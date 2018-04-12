/* 
 * File:   test_utilities.h
 * Author: Pantelis Sopasakis
 *
 * Created on May 26, 2017, 3:25 PM
 */

#ifndef TEST_UTILITIES_H
#define TEST_UTILITIES_H

#include "unit_test_util.h"
#include "linAlg.h"
#include "scs.h"
/* #include <time.h> */

#ifdef __cplusplus
extern "C" {
#endif

    bool testProjLinSysv2(char** str);

    bool testScaleArray(char** str);

    bool testGemm(char** str);

    bool testGemmCP(char** str);

    bool testGemmTransCP(char** str);

    bool testUnrolledDot(char** str);

    bool testSubtractArray(char** str);

    bool testNormDifference(char** str);

    bool testMillisToTime(char** str);

    bool testAxpy2(char** str);

    bool testCglsSquareMatrix(char** str);

    bool testCglsTallMatrix(char** str);

    bool testCglsFatMatrix(char** str);

    bool testQrLsTallMatrix(char** str);

    bool testSvdLsTallMatrix(char** str);

    bool testSvdLsRankDeficient(char** str);


#ifdef __cplusplus
}
#endif

#endif /* TEST_UTILITIES_H */

