#include <jni.h>    // JNI header provided by JDK
#include <stdio.h>  // C standard IO header
#include "HelloJNI.h"

JNIEXPORT void JNICALL Java_HelloJNI_sayHello(JNIEnv *env, jobject thisObj)
{
    printf("Hello World from C\n");
    return;
}
