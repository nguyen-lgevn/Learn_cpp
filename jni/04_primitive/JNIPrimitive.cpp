#include <jni.h>
#include <iostream>
#include "JNIPrimitive.h"

JNIEXPORT jdouble JNICALL Java_JNIPrimitive_average(JNIEnv* env, jobject obj, jint n1, jint n2)
{
    jdouble result;
    std::cout << "In C++, the numbers are " << n1 << " and " << n2 << std::endl;
    result = ((jdouble)n1+n2) / 2.0;
    return result;
}

JNIEXPORT jstring JNICALL Java_JNIPrimitive_sayHello(JNIEnv* env, jobject obj, jstring inJNIStr)
{
    const char* inCStr = env->GetStringUTFChars(inJNIStr, NULL);
    if (NULL == inCStr) return NULL;

    std::cout << "In C++, the received string is: " << inCStr << std::endl;
    std::cout << "String length: " << env->GetStringUTFLength(inJNIStr) << std::endl;
    env->ReleaseStringUTFChars(inJNIStr, inCStr);

    std::string outCStr;
    std::cout << "Enter a String: ";
    std::cin >> outCStr;
    return env->NewStringUTF(outCStr.c_str());
}

JNIEXPORT jdoubleArray JNICALL Java_JNIPrimitive_sumAndAverage
  (JNIEnv *env, jobject obj, jintArray intJNIArray)
{
    jint* inCArray = env->GetIntArrayElements(intJNIArray, NULL);
    if (NULL == inCArray) return NULL;
    jsize length = env->GetArrayLength(intJNIArray);

    jint sum = 0;
    for (int i = 0; i < length; i++)
        sum += inCArray[i];

    jdouble average = (jdouble)sum/length;
    env->ReleaseIntArrayElements(intJNIArray, inCArray, 0);

    jdouble outCArray[] = {sum, average};

    jdoubleArray outJNIArray = env->NewDoubleArray(2);
    if (NULL == outJNIArray) return NULL;
    env->SetDoubleArrayRegion(outJNIArray, 0, 2, outCArray);
    return outJNIArray;
}
