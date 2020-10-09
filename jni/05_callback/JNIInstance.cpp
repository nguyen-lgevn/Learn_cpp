#include <jni.h>
#include <iostream>
#include "JNIInstance.h"

JNIEXPORT void JNICALL Java_JNIInstance_modifyInstanceVariable(JNIEnv* env, jobject obj)
{
    jclass thisClass = env->GetObjectClass(obj);

    /* Use "I" for int, 
     * "B" for byte, 
     * "S" for short, 
     * J for long, 
     * F for float, 
     * D for double, 
     * C for char, 
     * Z for boolean
     * "[" prefix for array
     */
    jfieldID fidNumber = env->GetFieldID(thisClass, "number", "I");
    if (NULL == fidNumber) return;
    jint number = env->GetIntField(obj, fidNumber);
    std::cout << "In C++, the int is " << number << std::endl;
    number = 99;
    env->SetIntField(obj, fidNumber, number);
    
    jfieldID fidMessage = env->GetFieldID(thisClass, "message", "Ljava/lang/String;");
    if (NULL == fidMessage) return;
    jstring message = (jstring)env->GetObjectField(obj, fidMessage);
    const char* cStr = env->GetStringUTFChars(message, NULL);
    if (NULL == cStr) return;

    std::cout << "In C++, the string is " << cStr << std::endl;
    env->ReleaseStringUTFChars(message, cStr);

    message = env->NewStringUTF("Hello from C++");
    if (NULL == message) return;
    env->SetObjectField(obj, fidMessage, message);
    return;
}

JNIEXPORT void JNICALL Java_JNIInstance_modifyStaticVariable(JNIEnv* env, jobject obj)
{
    jclass thisClass = env->GetObjectClass(obj);

    /* Use "I" for int, 
     * "B" for byte, 
     * "S" for short, 
     * J for long, 
     * F for float, 
     * D for double, 
     * C for char, 
     * Z for boolean
     * "[" prefix for array
     */
    jfieldID fidNumber = env->GetStaticFieldID(thisClass, "dNumber", "D");
    if (NULL == fidNumber) 
    {
        std::cout << "Cannot find number\n";
        return;
    }
    jdouble number = env->GetStaticDoubleField(thisClass, fidNumber);
    std::cout << "In C++, the double is " << number << std::endl;
    number = 77.88;
    env->SetStaticDoubleField(thisClass, fidNumber, number);
    
    return;
}

JNIEXPORT void JNICALL Java_JNIInstance_nativeMethod(JNIEnv* env, jobject obj)
{
    jclass thisClass = env->GetObjectClass(obj);
    jmethodID midCallback = env->GetMethodID(thisClass, "callback", "()V");
    if (NULL == midCallback) return;
    std::cout << "In C++, call back Java's callback()" << std::endl;
    env->CallVoidMethod(obj, midCallback);
    
    jmethodID midCallbackStr = env->GetMethodID(thisClass, "callback", "(Ljava/lang/String;)V");
    if (NULL == midCallbackStr) return;
    std::cout << "In C++, call back Java's callback(String)" << std::endl;
    jstring message = env->NewStringUTF("Hello from C++");
    env->CallVoidMethod(obj, midCallbackStr, message);

    jmethodID midCallbackAverage = env->GetMethodID(thisClass, "callbackAverage", "(II)D");
    if (NULL == midCallbackAverage) return;
    jdouble average = env->CallDoubleMethod(obj, midCallbackAverage, 2, 3);
    std::cout << "In C++, the average is " << average << std::endl;

    jmethodID midCallbackStatic = env->GetStaticMethodID(thisClass, "callbackStatic","()Ljava/lang/String;");
    if (NULL == midCallbackStatic) return;
    jstring resultJNIStr = (jstring)env->CallStaticObjectMethod(thisClass, midCallbackStatic);
    const char* resultCStr = env->GetStringUTFChars(resultJNIStr, NULL);
    if (NULL == resultCStr) return;
    std::cout << "In C++, the returned string is " << resultCStr << std::endl;
    env->ReleaseStringUTFChars(resultJNIStr, resultCStr);
}
