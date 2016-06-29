#include "minmax_ai.h"
#include <string>
extern "C" {
//Turns the board into a linear array of size 25 and returns a string with its positions.
    JNIEXPORT jintArray JNICALL Java_com_pastacork_a5tactoe_Board_testFunc(JNIEnv * env, jobject obj, jobjectArray board){
        int len1 = env-> GetArrayLength(board);
        jobjectArray dim = (jobjectArray) env->GetObjectArrayElement(board, 0);
        int len2 = env -> GetArrayLength(dim);
        int **localArray;
        localArray = new int*[len1];
        int pos[2];
        bool done = false;
        for (int i = 0; i < len1 && !done; ++i){
            jintArray oneDim = (jintArray) env->GetObjectArrayElement(board, i);
            jint * element = env-> GetIntArrayElements(oneDim, 0);
            localArray[i] = new int[len2];
            for (int j = 0; j < len2; ++j){
                localArray[i][j] = element[j];
                if (localArray[i][j] == 0){
                    pos[0] = i;
                    pos[1] = j;
                    done = true;
                    break;
                }
            }
        }
        jintArray jarr = env->NewIntArray(2);
        jint * narr = env->GetIntArrayElements(jarr, NULL);
        narr[0] = pos[0];
        narr[1] = pos[1];
        env->ReleaseIntArrayElements(jarr, narr, NULL);
        return jarr;
    }

    JNIEXPORT jintArray JNICALL Java_com_pastacork_a5tactoe_Board_minimax(JNIEnv * env, jobject obj, jobjectArray board){
        int len1 = env-> GetArrayLength(board);
        jobjectArray dim = (jobjectArray) env->GetObjectArrayElement(board, 0);
        int len2 = env -> GetArrayLength(dim);
        int **localArray;
        localArray = new int*[len1];
        //char c[25];
        BOARD brd;
        for (int i = 0; i < len1; ++i){
            jintArray oneDim = (jintArray) env->GetObjectArrayElement(board, i);
            jint * element = env-> GetIntArrayElements(oneDim, 0);
            localArray[i] = new int[len2];
            for (int j = 0; j < len2; ++j){
                localArray[i][j] = element[j];
                //c[i*5 + j] = '0' + localArray[i][j];
                brd.boardM[i][j] = localArray[i][j];
            }
        }
        vector<int> moves = performMove(brd);
        jintArray jarr = env->NewIntArray(2);
        jint * narr = env->GetIntArrayElements(jarr, NULL);
        narr[0] = moves[0];
        narr[1] = moves[1];
        env->ReleaseIntArrayElements(jarr, narr, NULL);
        return jarr;
        //return testCPPFunc(env, obj);
    }
}