#include <jni.h>
#include <iostream>
#include "HelloJNICpp.h"

//using namespace std;

JNIEXPORT void JNICALL Java_HelloJNICpp_sayHello(JNIEnv *env, jobject thisObj)
{
    std::cout << "Hello world from C++!" << std::endl;
    return;
}
