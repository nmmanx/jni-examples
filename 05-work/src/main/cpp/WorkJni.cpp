#include <jni.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
#include <assert.h>

#define WORK_CLASS  "jniexamples/work/Work"

struct WorkInfo {
    std::thread thread;
    jclass workClass;
    jobject workObj;
    jmethodID onStartMd;
    jmethodID onProgressMd;
    jmethodID onCompletedMd;
} g_workInfo;

static JavaVM *g_jvm;

class Work {
public:
    static void run(void *args)
    {
        JNIEnv *env = NULL;
        const int max = 10;

        jlong stat = g_jvm->AttachCurrentThread((void**)&env, NULL);
        if (stat != JNI_OK || env == NULL) {
            return;
        }

        env->CallVoidMethod(g_workInfo.workObj, g_workInfo.onStartMd);
        for (int i = 1; i <= max; i++) {
            env->CallVoidMethod(g_workInfo.workObj, g_workInfo.onProgressMd, (float)i / max);
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        env->CallVoidMethod(g_workInfo.workObj, g_workInfo.onCompletedMd, true);

        env->DeleteGlobalRef(g_workInfo.workObj);
        g_jvm->DetachCurrentThread();
    }
};

static void start(JNIEnv *env, jobject obj)
{
    if (g_workInfo.thread.joinable()) {
        return;
    }

    g_workInfo.workObj = env->NewGlobalRef(obj);
    g_workInfo.thread = std::thread(&Work::run, nullptr);
}

static void waitForCompleted(JNIEnv *env, jobject obj)
{
    if (g_workInfo.thread.joinable()) {
        g_workInfo.thread.join();
    }
}

static const JNINativeMethod methods[] = {
    { "start", "()V", (void*)start },
    { "waitForCompleted", "()V", (void*)waitForCompleted }
};

jint JNI_OnLoad(JavaVM *vm, void *reserved)
{
    JNIEnv *env = NULL;
    g_jvm = vm;

    if (vm->GetEnv((void**)&env, JNI_VERSION_1_4) != JNI_OK) {
        std::cout << "Unable to get JNIEnv\n";
        return -1;
    }

    jclass clazz = env->FindClass(WORK_CLASS);
    if (clazz == NULL) {
        std::cout << "Unable to find " WORK_CLASS "\n";
        return -1;
    }

    g_workInfo.workClass = (jclass)env->NewGlobalRef((jobject)clazz);

    g_workInfo.onStartMd = env->GetMethodID(clazz, "onStart", "()V");
    assert(g_workInfo.onStartMd != NULL);

    g_workInfo.onProgressMd = env->GetMethodID(clazz, "onProgress", "(F)V");
    assert(g_workInfo.onProgressMd != NULL);

    g_workInfo.onCompletedMd = env->GetMethodID(clazz, "onCompleted", "(Z)V");
    assert(g_workInfo.onCompletedMd != NULL);

    if (env->RegisterNatives(clazz, methods, sizeof(methods) / sizeof(methods[0])) < 0) {
        std::cout << "Cannot register native methods\n";
        return -1;
    }

    return JNI_VERSION_1_4;
}