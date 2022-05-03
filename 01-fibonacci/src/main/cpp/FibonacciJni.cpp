#include <jni.h>
#include <iostream>

#include "FibonacciCore.h"

#define FIBONACCI_CLASS "jniexamples/fibo/Fibonacci"

enum {
    ALGO_RECURSION  = 1,
    ALGO_DYNAMIC    = 2
};

static jint fibonacci_native(JNIEnv *env, jclass clazz, jint n, jint algo)
{
    jint result = 0;

    switch (algo) {
    case ALGO_RECURSION:
        result = fibo_recursion(n);
        break;
    case ALGO_DYNAMIC:
        result = fibo_dynamic(n);
        break;
    default:
        result = fibo_recursion(n);
        break;
    }

    return result;
}

static const JNINativeMethod methods[] = {
    { "fibo", "(II)I", (void*) fibonacci_native }
};

/* Called when System.loadLibrary() */
jint JNI_OnLoad(JavaVM *vm, void *reserved)
{
    JNIEnv *env = NULL;

    if (vm->GetEnv((void**)&env, JNI_VERSION_1_4) != JNI_OK) {
        std::cout << "Unable to get JNIEnv\n";
        return -1;
    }

    jclass clazz = env->FindClass(FIBONACCI_CLASS);
    if (clazz == NULL) {
        std::cout << "Unable to find " FIBONACCI_CLASS "\n";
        return -1;
    }

    if (env->RegisterNatives(clazz, methods, sizeof(methods) / sizeof(methods[0])) < 0) {
        std::cout << "Cannot register native methods\n";
        return -1;
    }

    return JNI_VERSION_1_4;
}