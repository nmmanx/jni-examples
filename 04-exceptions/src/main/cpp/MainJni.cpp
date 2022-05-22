#include <jni.h>
#include <iostream>
#include <assert.h>

#define MAIN_CLASS      "jniexamples/exceptions/Main"
#define HELPER_CLASS    "jniexamples/exceptions/Helper"
#define RUNTIME_EXCEPTION_CLASS     "java/lang/RuntimeException"

static jclass g_runtimeExpClass;

static void doSomething(JNIEnv* env, jclass clazz, jobject helper)
{
    jclass helperClass = env->FindClass(HELPER_CLASS);
    assert(helperClass != NULL);

    jmethodID helpMd = env->GetMethodID(helperClass, "help", "()V");
    assert(helpMd != NULL);

    env->CallVoidMethod(helper, helpMd);

    if (env->ExceptionCheck() == JNI_TRUE) {
        std::cout << "Helper.help() throws an exception:\n" << std::flush;
        env->ExceptionDescribe();

         // Clear the IllegalArgumentException thrown by Helper.help()
        env->ExceptionClear();

        // Throw another RuntimeException
        env->ThrowNew(g_runtimeExpClass, "A RuntimeException from native code");
    }
}

static const JNINativeMethod methods[] = {
    { "doSomething", "(Ljniexamples/exceptions/Helper;)V", (void*)doSomething }
};

jint JNI_OnLoad(JavaVM *vm, void *reserved)
{
    JNIEnv *env = NULL;

    if (vm->GetEnv((void**)&env, JNI_VERSION_1_4) != JNI_OK) {
        std::cout << "Unable to get JNIEnv\n";
        return -1;
    }

    jclass clazz = env->FindClass(MAIN_CLASS);
    if (clazz == NULL) {
        std::cout << "Unable to find " MAIN_CLASS "\n";
        return -1;
    }

    g_runtimeExpClass = env->FindClass(RUNTIME_EXCEPTION_CLASS);
    assert(g_runtimeExpClass != NULL);

    if (env->RegisterNatives(clazz, methods, sizeof(methods) / sizeof(methods[0])) < 0) {
        std::cout << "Cannot register native methods\n";
        return -1;
    }

    return JNI_VERSION_1_4;
}