#include <jni.h>
#include <iostream>
#include <assert.h>

#define FACTORY_CLASS   "jniexamples/factory/Factory"
#define PRODUCT_CLASS   "jniexamples/factory/Product"

struct ProductClassInfo {
    jclass clazz;
    jmethodID cstr;
    jfieldID idField;
    jfieldID nameField;
    jfieldID descField;
    jfieldID priceField;
} g_productClassInfo;

static void cacheProductClassInfo(JNIEnv *env)
{
    jclass clazz = env->FindClass(PRODUCT_CLASS);
    assert(clazz != NULL);
    g_productClassInfo.clazz = (jclass)env->NewGlobalRef(clazz);

    g_productClassInfo.cstr= env->GetMethodID(clazz, "<init>", "()V");
    assert(g_productClassInfo.cstr != NULL);

    g_productClassInfo.idField = env->GetFieldID(clazz, "mId", "J");
    assert(g_productClassInfo.idField != NULL);

    g_productClassInfo.nameField = env->GetFieldID(clazz, "mName", "Ljava/lang/String;");
    assert(g_productClassInfo.nameField != NULL);

    g_productClassInfo.descField = env->GetFieldID(clazz, "mDesc", "Ljava/lang/String;");
    assert(g_productClassInfo.descField != NULL);

    g_productClassInfo.priceField = env->GetFieldID(clazz, "mPrice", "I");
    assert(g_productClassInfo.priceField != NULL);
}

static jobject buildFromNative(JNIEnv *env, jclass clazz, jlong id, jstring name, jstring desc, jint price)
{
    jobject obj = env->NewObject(g_productClassInfo.clazz, g_productClassInfo.cstr);
    assert(obj != NULL);

    env->SetLongField(obj, g_productClassInfo.idField, id);
    env->SetObjectField(obj, g_productClassInfo.nameField, name);
    env->SetObjectField(obj, g_productClassInfo.descField, desc);
    env->SetIntField(obj, g_productClassInfo.priceField, price);

    return obj;
}

static const JNINativeMethod methods[] = {
    { "buildFromNative", "(JLjava/lang/String;Ljava/lang/String;I)Ljniexamples/factory/Product;", (void*)buildFromNative }
};

jint JNI_OnLoad(JavaVM *vm, void *reserved)
{
    JNIEnv *env = NULL;

    if (vm->GetEnv((void**)&env, JNI_VERSION_1_4) != JNI_OK) {
        std::cout << "Unable to get JNIEnv\n";
        return -1;
    }

    jclass clazz = env->FindClass(FACTORY_CLASS);
    if (clazz == NULL) {
        std::cout << "Unable to find " FACTORY_CLASS "\n";
        return -1;
    }

    cacheProductClassInfo(env);

    if (env->RegisterNatives(clazz, methods, sizeof(methods) / sizeof(methods[0])) < 0) {
        std::cout << "Cannot register native methods\n";
        return -1;
    }

    return JNI_VERSION_1_4;
}