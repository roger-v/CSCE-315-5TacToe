#include "minmax_ai.h"
#include <string>
extern "C" {
//Turns the board into a linear array of size 25 and returns a string with its positions.
    JNIEXPORT jstring JNICALL Java_com_pastacork_a5tactoe_Board_testFunc(JNIEnv * env, jobject obj, jobjectArray board){
        int len1 = env-> GetArrayLength(board);
        jobjectArray dim = (jobjectArray) env->GetObjectArrayElement(board, 0);
        int len2 = env -> GetArrayLength(dim);
        int **localArray;
        localArray = new int*[len1];
        char c[25];
        for (int i = 0; i < len1; ++i){
            jintArray oneDim = (jintArray) env->GetObjectArrayElement(board, i);
            jint * element = env-> GetIntArrayElements(oneDim, 0);
            localArray[i] = new int[len2];
            for (int j = 0; j < len2; ++j){
                localArray[i][j] = element[j];
                c[i*5 + j] = '0' + localArray[i][j];
            }
        }
        return env->NewStringUTF(c);
        //return testCPPFunc(env, obj);
    }
}