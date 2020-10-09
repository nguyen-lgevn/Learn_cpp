#include <jni.h>
#include <iostream>
#include "JNIObjArray.h"

JNIEXPORT jobject JNICALL Java_JNIObjArray_getIntegerObject(JNIEnv *env, jobject obj, jint number)
{
    jclass cls = env->FindClass("java/lang/Integer");
    jmethodID midInit = env->GetMethodID(cls, "<init>", "(I)V");
    if (NULL == midInit) return NULL;
    jobject newObj = env->NewObject(cls, midInit, number);

    jmethodID midToString = env->GetMethodID(cls, "toString", "()Ljava/lang/String;");
    if (NULL == midToString) return NULL;
    jstring resultStr = (jstring)env->CallObjectMethod(newObj, midToString);
    const char* resultCStr = env->GetStringUTFChars(resultStr, NULL);
    std::cout << "In C++, the number is " << resultCStr << std::endl;
    return newObj;
}

JNIEXPORT jobjectArray JNICALL Java_JNIObjArray_sumAndAverage
  (JNIEnv *env, jobject obj, jobjectArray inJNIArray)
{
    jclass clsInteger = env->FindClass("java/lang/Integer");
    jmethodID midIntValue = env->GetMethodID(clsInteger, "intValue", "()I");
    if (NULL == midIntValue) return NULL;

    jsize length = env->GetArrayLength(inJNIArray);
    jint sum = 0;
    for (int i = 0; i < length; i++) {
        jobject objInteger = env->GetObjectArrayElement(inJNIArray, i);
        if (NULL == objInteger) return NULL;
        jint value = env->CallIntMethod(objInteger, midIntValue);
        sum += value;
    }
    double average = (double)sum / length;
    std::cout << "In C++, the sum is " << sum << std::endl;
    std::cout << "In C++, the average is " << average << std::endl;

    jclass classDouble = env->FindClass("java/lang/Double");
    jobjectArray outJNIArray = env->NewObjectArray(2, classDouble, NULL);
    jmethodID midDoubleInit = env->GetMethodID(classDouble, "<init>", "(D)V");
    if (NULL == midDoubleInit) return NULL;
    jobject objSum = env->NewObject(classDouble, midDoubleInit, (double)sum);
    jobject objAve = env->NewObject(classDouble, midDoubleInit, average);
    env->SetObjectArrayElement(outJNIArray, 0, objSum);
    env->SetObjectArrayElement(outJNIArray, 1, objAve);
    return outJNIArray;
}
