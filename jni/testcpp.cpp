//
// Created by PASTACORK on 6/28/2016.
//

#include "testcpp.h"

using namespace std;

JNIEXPORT jstring JNICALL testCPPFunc(JNIEnv* env, jobject thiz){
    char a = '0' + 7;
    char b = '0' + 3;
    char c[] = {a, b};
    return (env)->NewStringUTF(c);
}