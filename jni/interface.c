#include "testcpp.h"

jstring Java_com_pastacork_a5tactoe_Board_testFunc(JNIEnv * env, jobject obj){
    return testCPPFunc(env, obj);
}