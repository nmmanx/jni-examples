#include <jni.h>
#include <iostream>

#define ECHO_CLASS          "jniexamples/echo/Echo"
#define JAVAOBJECT_CLASS    "jniexamples/echo/JavaObject"

static void sendInteger(JNIEnv *env, jclass clazz, jint n1, jshort n2, jlong n3)
{

}

static void sendDecimal(JNIEnv *env, jclass clazz, jfloat f1, jdouble f2)
{

}

static void sendChar(JNIEnv *env, jclass clazz, jchar ch)
{

}

static void sendString(JNIEnv *env, jclass clazz, jstring str)
{

}

static void sendBoolean(JNIEnv *env, jclass clazz, jboolean b)
{

}

static void sendIntegerArray(JNIEnv *env, jclass clazz, jintArray arr)
{

}

static void sendObject(JNIEnv *env, jclass clazz, jobject obj)
{

}

static void sendObjectArray(JNIEnv *env, jclass clazz, jobjectArray objArr)
{

}

static const JNINativeMethod methods[] = {
    { "sendInteger", "(ISJ)V", (void*)sendInteger },
    { "sendDecimal", "(FD)V", (void*)sendDecimal },
    { "sendChar", "(C)V", (void*)sendChar },
    { "sendString", "(Ljava/lang/String;)V", (void*)sendString },
    { "sendBoolean", "(Z)V", (void*)sendBoolean },
    { "sendIntegerArray", "([I)V", (void*)sendIntegerArray },
    { "sendObject", "(Ljniexamples/echo/JavaObject;)V", (void*)sendObject },
    { "sendObjectArray", "([Ljniexamples/echo/JavaObject;)V", (void*)sendObjectArray },
};

jint JNI_OnLoad(JavaVM *vm, void *reserved)
{
    JNIEnv *env = NULL;

    if (vm->GetEnv((void**)&env, JNI_VERSION_1_4) != JNI_OK) {
        std::cout << "Unable to get JNIEnv\n";
        return -1;
    }

    jclass clazz = env->FindClass(ECHO_CLASS);
    if (clazz == NULL) {
        std::cout << "Unable to find " ECHO_CLASS "\n";
        return -1;
    }

    if (env->RegisterNatives(clazz, methods, sizeof(methods) / sizeof(methods[0])) < 0) {
        std::cout << "Cannot register native methods\n";
        return -1;
    }

    return JNI_VERSION_1_4;
}