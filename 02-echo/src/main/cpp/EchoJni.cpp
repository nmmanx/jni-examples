#include <jni.h>
#include <iostream>
#include <assert.h>

#define ECHO_CLASS          "jniexamples/echo/Echo"
#define JAVAOBJECT_CLASS    "jniexamples/echo/JavaObject"

static jstring getJavaObjectName(JNIEnv *env, jobject obj)
{
    jclass javaObjClazz = env->FindClass(JAVAOBJECT_CLASS);
    assert(javaObjClazz != NULL);

    jmethodID methodId = env->GetMethodID(javaObjClazz, "getName", "()Ljava/lang/String;");
    assert(methodId != NULL);

    return (jstring)env->CallObjectMethod(obj, methodId);
}

static void sendInteger(JNIEnv *env, jclass clazz, jint n1, jshort n2, jlong n3)
{
    std::cout << "Received integer: " << n1 << std::endl;
    std::cout << "Received short: " << n2 << std::endl;
    std::cout << "Received long: " << n3 << std::endl;
}

static void sendDecimal(JNIEnv *env, jclass clazz, jfloat f1, jdouble f2)
{
    std::cout << "Received float: " << f1 << std::endl;
    std::cout << "Received double: " << f2 << std::endl;
}

static void sendChar(JNIEnv *env, jclass clazz, jchar ch)
{
    std::cout << "Received char: \'" << (char)ch << "\"\n";
}

static void sendString(JNIEnv *env, jclass clazz, jstring str)
{
    jboolean isCopy;
    const char *chars = env->GetStringUTFChars(str, &isCopy);
    std::cout << "Received string: \"" << chars << "\"\n";
    env->ReleaseStringUTFChars(str, chars);
}

static void sendBoolean(JNIEnv *env, jclass clazz, jboolean b)
{
    std::cout << "Received boolean: " << (b == JNI_TRUE ? "true" : "false") << std::endl;
}

static void sendIntegerArray(JNIEnv *env, jclass clazz, jintArray arr)
{
    jboolean isCopy;
    jsize sz = env->GetArrayLength(arr);
    jint *arr_p = env->GetIntArrayElements(arr, &isCopy);

    if (arr_p == NULL) {
        return;
    }

    if (sz > 0) {
        std::cout << "Received integer array: [";
        for (jsize i = 0; i < sz - 1; ++i) {
            std::cout << arr_p[i] << ", ";
        }
        std::cout << arr_p[sz-1] << "]\n";
    }

    env->ReleaseIntArrayElements(arr, arr_p, JNI_ABORT);
}

static void sendObject(JNIEnv *env, jclass clazz, jobject obj)
{   
    jboolean isCopy;
    jstring name = getJavaObjectName(env, obj);

    const char *chars = env->GetStringUTFChars(name, &isCopy);
    std::cout << "Received object: Object{\"" << chars << "\"}" << std::endl;
    env->ReleaseStringUTFChars(name, chars);
}

static void sendObjectArray(JNIEnv *env, jclass clazz, jobjectArray objArr)
{
    jsize sz = env->GetArrayLength(objArr);

    auto print = [env](jobject o) {
        jboolean isCopy;
        jstring name = getJavaObjectName(env, o);
        const char *chars = env->GetStringUTFChars(name, &isCopy);
        std::cout << "Object{\"" << chars << "\"}";
        env->ReleaseStringUTFChars(name, chars);
    };

    if (sz > 0) {
        std::cout << "Received object array: [";
        for (jsize i = 0; i < sz - 1; ++i) {
            print(env->GetObjectArrayElement(objArr, i));
            std::cout << ", ";
        }
        print(env->GetObjectArrayElement(objArr, sz - 1));
        std::cout << "]\n";
    }
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