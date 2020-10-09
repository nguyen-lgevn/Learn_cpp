#include <jni.h>
#include <iostream>
#include "JNIReferences.h"

static jclass classInteger;
static jmethodID midIntegerInit;

jobject getInteger(JNIEnv *env, jobject obj, jint number)
{
    if (NULL == classInteger)
    {
        std::cout << "Find Java.lang.Integer\n";
        jclass classIntegerLocal = env->FindClass("java/lang/Integer");
        classInteger = (jclass)env->NewGlobalRef(classIntegerLocal);
        env->DeleteLocalRef(classIntegerLocal);
    }
    if (NULL == classInteger)
        return NULL;

    if (NULL == midIntegerInit)
    {
        std::cout << "Get Method ID for java.lang.Integer's Constructor\n";
        midIntegerInit = env->GetMethodID(classInteger, "<init>", "(I)V");
    }
    if (NULL == midIntegerInit)
        return NULL;

    jobject newObj = env->NewObject(classInteger, midIntegerInit, number);
    std::cout << "In C++, constructed java.lang.Integer with number " << number << std::endl;
    return newObj;
}

JNIEXPORT jobject JNICALL Java_JNIReferences_getFooIntegerObject(JNIEnv *env, jobject thisObj, jint number) {
    std::cout << __FUNCTION__ << std::endl;
    return getInteger(env, thisObj, number);
}

JNIEXPORT jobject JNICALL Java_JNIReferences_getBarIntegerObject(JNIEnv *env, jobject thisObj, jint number) {
    return getInteger(env, thisObj, number);
}
