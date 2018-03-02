#include "test_utilities.h"

bool testProjLinSysv2(char** str) {

    scs_int n = 5, m = 10, l = n + m + 1, i;
    scs_float *u_t, *u, *h, *g;
    scs_float gTh = 2.2;
    const scs_float rho_x = 1.0;
    scs_float *expected_result;
    bool test_pass = false;
    float tolerance = 1e-6;


    /* memory allocation */
    expected_result = malloc(l * sizeof (scs_float));
    u = malloc(l * sizeof (scs_float));
    u_t = malloc(l * sizeof (scs_float));
    h = malloc((l - 1) * sizeof (scs_float));
    g = malloc((l - 1) * sizeof (scs_float));


    for (i = 0; i < l; ++i) {
        u_t[i] = 0.5 * (i + 1);
    }

    for (i = 0; i < l - 1; ++i) {
        h[i] = 0.2 * (i + 1);
        g[i] = 0.8 * (i + 1);
    }
    /*  memcpy(u_t, u, l * sizeof (scs_float)); */

    scaleArray(u_t, rho_x, n);

    addScaledArray(u_t, h, l - 1, -u_t[l - 1]);
    addScaledArray(u_t, h, l - 1,
            -innerProd(u_t, g, l - 1) / (gTh + 1));
    scaleArray(&(u_t[n]), -1, m);

    /*   status = solveLinSys(A, stgs, w->p, w->u_t, w->u, iter); */
    u_t[l - 1] += innerProd(u_t, h, l - 1);

    expected_result[0] = 67.10;
    expected_result[1] = 134.20;
    expected_result[2] = 201.30;
    expected_result[3] = 268.40;
    expected_result[4] = 335.50;
    expected_result[5] = -402.60;
    expected_result[6] = -469.70;
    expected_result[7] = -536.80;
    expected_result[8] = -603.90;
    expected_result[9] = -671.00;
    expected_result[10] = -738.10;
    expected_result[11] = -805.20;
    expected_result[12] = -872.30;
    expected_result[13] = -939.40;
    expected_result[14] = -1006.50;
    expected_result[15] = -15156.60;


    test_pass = assertEqualsArray(u_t, expected_result, l, tolerance);

    /* free memory */
    free(u);
    u = NULL;
    free(u_t);
    u_t = NULL;
    free(h);
    h = NULL;
    free(g);
    g = NULL;
    free(expected_result);
    expected_result = NULL;
    if (!test_pass) {
        FAIL_WITH_MESSAGE(str, "testProjLinSysv2 failed");
    }

    SUCCEED(str);
}

bool testScaleArray(char** str) {
    const scs_int N = 10;
    float tolerance = 1e-6;
    unsigned int i;
    bool test_pass = false;
    scs_float * a = malloc(N * sizeof (scs_float));
    scs_float * expected_result = malloc(N * sizeof (scs_float));
    const scs_float b = 3.23412;

    for (i = 0; i < N; ++i) {
        a[i] = 0.5 * (i + 1);
        expected_result[i] = b * a[i];
    }

    scaleArray(a, b, N);
    test_pass = assertEqualsArray(a, expected_result, N, tolerance);

    /* free memory */
    free(a);
    a = NULL;
    free(expected_result);
    expected_result = NULL;
    if (!test_pass) {
        FAIL_WITH_MESSAGE(str, "scaleArray failed");
    }
    SUCCEED(str); /* if it reaches this point, it has succeeded */
}

bool testGemm(char** str) {
    const double A[6] = {0.8147,
        0.9058,
        0.1270,
        0.9134,
        0.6324,
        0.0975};
    const double B[6] = {0.2785,
        0.5469,
        0.9575,
        0.9649,
        0.1576,
        0.9706};
    double C[4] = {0.9572,
        0.4854,
        0.8003,
        0.1419};
    const double Cexp[4] = {2.3653,
        1.3934,
        2.3106,
        0.8401};
    const double alpha = 0.5;
    const double beta = 2;
    dgemm_nn(2, 2, 3,
            alpha, A,
            1, 2,
            B,
            1, 3,
            beta, C,
            1, 2);

    ASSERT_EQUAL_ARRAY_OR_FAIL(C, Cexp, 4, 1e-4, str, "gemm failed");
    SUCCEED(str);

}

bool testGemmCP(char** str) {
    const double A[10] = {
        0.334430155748757,
        -0.119893174350795,
        0.804005060428243,
        -0.067975658376914,
        -1.063394117875069,
        0.809765549484799,
        -1.878509454657401,
        -0.259736781357468,
        0.470502094834760,
        0.320050300435137
    };
    const double B[15] = {
        0.242754814623263,
        -0.103589012251697,
        -0.454961543295210,
        -0.413269912824790,
        1.497631598138995,
        -0.128084953472689,
        2.266925189882620,
        -0.254500560127930,
        -0.711248533058385,
        -0.369507289387400,
        -1.999207676978967,
        -0.555866380148284,
        0.587186741401126,
        1.004782851967581,
        -0.585280006989040
    };
    double C[6] = {
        -0.774073198694521,
        -0.960044604299499,
        -2.022434124346632,
        -0.323079592516537,
        1.037274430734777,
        0.420892205865074
    };
    const double alpha = -0.286281752586377;
    const double beta = 3.194915595797473;
    const double Cexp[6] = {
        -3.034975746827981,
        -3.123425247115062,
        -7.381229796362662,
        -0.952525926453145,
        4.431303305975694,
        1.257495836652682
    };

    matrixMultiplicationColumnPacked(2, 3, 5, alpha, A, beta, B, C);

    ASSERT_EQUAL_ARRAY_OR_FAIL(C, Cexp, 4, 1e-14, str, "gemm failed");

    SUCCEED(str);
}

bool testGemmTransCP(char** str) {
    const double A[12] = {
        0.698299663682011,
        -1.627423017907931,
        -1.372695305499414,
        -1.100828998920425,
        1.619000819707846,
        -0.600157916750174,
        -0.540089717235530,
        1.484871682894813,
        1.809840858337382,
        0.919301984685824,
        -0.212130772097334,
        -0.095040503915385
    };
    const double B[8] = {
        0.701256481812284,
        0.876974554050047,
        -2.190732553342963,
        0.687223989397896,
        0.905368244420720,
        2.186309802484150,
        -0.496517337448137,
        0.288763931098904
    };
    double C[6] = {
        -1.608876042935446,
        -0.040192422065262,
        1.723531705742089,
        0.445855130092155,
        -0.628575736932150,
        -0.462395267263025
    };
    const double alpha = -0.023912990352431;
    const double beta = 0.916952300228893;
    const double Cexp[6] = {
        -1.506664428673252,
        -0.104113242719988,
        1.521217097262638,
        0.470096441685509,
        -0.596714407327636,
        -0.513102186175089
    };
    matrixMultiplicationTransColumnPacked(3, 2, 4, alpha, A, beta, B, C);
    ASSERT_EQUAL_ARRAY_OR_FAIL(C, Cexp, 4, 1e-5, str, "gemm failed");
    SUCCEED(str);
}

bool testUnrolledDot(char** str) {
    const scs_float x[4] = {5., 2., 3., 4.};
    const scs_float y[4] = {0.1, 0.2, 0.5, -0.9};
    const scs_float a[5] = {5.0, 6.0, 7.0, 8.0, 9.0};
    const scs_float b[5] = {11.0, 13.0, 15.0, 17.0, 19.0};
    const scs_float c[6] = {-1.2, 3.4, 5.6, 7.8, 9.1, 11.12};
    const scs_float d[6] = {2.3, 4.5, 6.7, 8.9, 10.11, 12.13};
    const scs_float p[11] = {0.554259561551264, -2.159803537045049, -0.372961114202917,
        -2.592374718571431, 0.549237254991523, 0.535999299756211, -0.188665249567086,
        0.760181191234408, 1.033831426574950, -0.196086216446758, 0.474596953309341};
    const scs_float q[11] = {-1.2360603341291734, -0.7844101929878990, 0.7651738841267504,
        -0.8603726595864287, 1.0311516752375671, 0.5283233936417885, -1.2091816279319294,
        -0.1549870848290139, -0.9608099563757425, 0.7599149377251431, 0.0224256807626837};
    /*
        const unsigned n = 5e6;
        scs_float * big_x = malloc(n * sizeof (scs_float));
        scs_float * big_y = malloc(n * sizeof (scs_float));    
        scs_int i;
     */

    scs_float ip;
    /*
        clock_t t;
     */

    ip = innerProd(x, y, 4);
    ASSERT_EQUAL_FLOAT_OR_FAIL(ip, -1.2, 1e-6, str, "inn prod 1");
    ip = innerProd(a, b, 5);
    ASSERT_EQUAL_FLOAT_OR_FAIL(ip, 545.0, 1e-6, str, "inn prod 2");
    ip = innerProd(c, d, 6);
    ASSERT_EQUAL_FLOAT_OR_FAIL(ip, 346.3666, 1e-6, str, "inn prod 3");
    ip = innerProd(p, q, 11);
    ASSERT_EQUAL_FLOAT_OR_FAIL(ip, 2.78226083574042, 1e-10, str, "inn prod 4");
    ip = innerProd(p, q, 7);
    ASSERT_EQUAL_FLOAT_OR_FAIL(ip, 4.03176031557307, 1e-10, str, "inn prod 5");
    ip = innerProd(p, q, 8);
    ASSERT_EQUAL_FLOAT_OR_FAIL(ip, 3.91394204880181, 1e-10, str, "inn prod 6");
    ip = innerProd(p, q, 1);
    ASSERT_EQUAL_FLOAT_OR_FAIL(ip, -0.685098258845344, 1e-10, str, "inn prod 7");
    ip = innerProd(p, q, 2);
    ASSERT_EQUAL_FLOAT_OR_FAIL(ip, 1.00907365046411, 1e-10, str, "inn prod 8");
    ip = innerProd(p, q, 0);
    ASSERT_EQUAL_FLOAT_OR_FAIL(ip, 0.0f, 1e-10, str, "inn prod 9");
    ip = innerProd(p, q, -1);
    ASSERT_EQUAL_FLOAT_OR_FAIL(ip, 0.0f, 1e-10, str, "inn prod 10");

    /*
        t = clock();
        for (i = 0; i < 500; ++i) {
            ip = innerProd(big_x, big_y, n);
        }
        t = clock() - t;
        double elapsed_time = t / (double) CLOCKS_PER_SEC;
        printf("Elapsed time: %g.\n", elapsed_time);
        scs_free(big_x);
        scs_free(big_y);
     */
    SUCCEED(str);
}

bool testLinAlg(char** str) {
#define n_dim_linalg 97
    scs_float x[n_dim_linalg];
    scs_float y[n_dim_linalg];
    unsigned int i = 0;
    unsigned int j;
    for (j = 1; j < 10; ++j) {
        for (i = 0; i < n_dim_linalg; ++i) {
            x[i] = SQRTF(0.1 * i + 1);
            y[i] = sin(i / 20);
        }
        subtractArray(x, y, n_dim_linalg - j);
        for (i = 0; i < n_dim_linalg - j; ++i) {
            ASSERT_EQUAL_FLOAT_OR_FAIL(x[i], SQRTF(0.1 * i + 1) - sin(i / 20), 1e-10, str, "wrong");
        }
    }
    SUCCEED(str);
}

bool testMillisToTime(char** str) {
    scs_float t;
    scs_int hours;
    scs_int minutes;
    scs_int seconds;
    scs_float millis;
    scs_float tol = 1e-14;

    t = 100; /* ms */
    millisToTime(t, &hours, &minutes, &seconds, &millis);
    ASSERT_EQUAL_INT_OR_FAIL(hours, 0, str, "h");
    ASSERT_EQUAL_INT_OR_FAIL(minutes, 0, str, "m");
    ASSERT_EQUAL_INT_OR_FAIL(seconds, 0, str, "s");
    ASSERT_EQUAL_FLOAT_OR_FAIL(millis, 0.1, tol, str, "ms");

    t = 1000 * 60 * 5 + 1000 * 12; /* ms */
    millisToTime(t, &hours, &minutes, &seconds, &millis);
    ASSERT_EQUAL_INT_OR_FAIL(hours, 0, str, "h");
    ASSERT_EQUAL_INT_OR_FAIL(minutes, 5, str, "m");
    ASSERT_EQUAL_INT_OR_FAIL(seconds, 12, str, "s");
    ASSERT_EQUAL_FLOAT_OR_FAIL(millis, 0.0, tol, str, "ms");

    t = 1000 * 60 * 60 + 1000 * 60 * 7 + 1000 * 15; /* ms */
    millisToTime(t, &hours, &minutes, &seconds, &millis);
    ASSERT_EQUAL_INT_OR_FAIL(hours, 1, str, "h");
    ASSERT_EQUAL_INT_OR_FAIL(minutes, 7, str, "m");
    ASSERT_EQUAL_INT_OR_FAIL(seconds, 15, str, "s");
    ASSERT_EQUAL_FLOAT_OR_FAIL(millis, 0.0, tol, str, "ms");

    t = 1000 * 60 * 60 * 250 + 1000 * 60 * 59 + 1000 * 59 + 500; /* ms */
    millisToTime(t, &hours, &minutes, &seconds, &millis);
    ASSERT_EQUAL_INT_OR_FAIL(hours, 250, str, "h");
    ASSERT_EQUAL_INT_OR_FAIL(minutes, 59, str, "m");
    ASSERT_EQUAL_INT_OR_FAIL(seconds, 59, str, "s");
    ASSERT_EQUAL_FLOAT_OR_FAIL(millis, 0.5, tol, str, "ms");


    SUCCEED(str);
}

bool testAxpy2(char** str) {
    scs_int i;
    const scs_int l = 10;
    scs_float x[10];
    scs_float u[10];
    scs_float v[10];
    scs_float x_exp[] = {
        -8.31500000000000,
        -12.92483005625000,
        -18.58331738662000,
        -24.41433470338000,
        -30.33466011249999,
        -36.31205831449999,
        -42.32999708489000,
        -48.37865552442999,
        -54.45163477310999,
        -60.54449016874999
    };

    scs_float a = 2.5;
    scs_float b = -3.8;

    for (i = 0; i < l; ++i) {
        u[i] = 2.0 * i + SQRTF(5.0 * i) + 1.234;
        v[i] = 3.0 * (i + 1.0) + SQRTF(i);
        x[i] = -1e3 * (i - 0.1);
    }

    for (i = 0; i < 6; ++i) {
        axpy2(x, u, v, a, b, l - i);
        ASSERT_EQUAL_ARRAY_OR_FAIL(x, x_exp, l - i, 1e-5, str, "?");
    }

    SUCCEED(str);
}

bool testCglsSquareMatrix(char** str) {
    int k;
    const scs_int rowsA = 5;
    const scs_int colsA = 5;
    const scs_float A[25] = {0.5370, 1.8330, -2.2590, 0.8620, 0.3180, -1.3080, -0.4340,
        0.3420, 3.5780, 2.7690, -1.3500, 3.0340, 0.7250, -0.0640, 0.7140, -0.2050,
        -0.1250, 1.4890, 1.4090, 1.4170, 0.6710, -1.2080, 0.7170, 1.6300, 0.4880};
    const scs_float b[5] = {0.8880, -1.1480, -1.0690, -0.8100, -2.9450};
    const scs_float x_correct[5] = {-0.613341864609879, 0.040545395435958, 0.954267555485693,
        -3.450896441946640, 2.758905197961816};
    scs_float x[5] = {1., 1., 1., 1., 1.};
    scs_float * wspace;
    scs_float tol = 1e-7;
    scs_int maxiter = 20;
    scs_int status;

    wspace = cgls_malloc_workspace(rowsA, colsA);
    ASSERT_TRUE_OR_FAIL(wspace != NULL, str, "space is NULL");
    status = cgls(rowsA, colsA, A, b, x, tol, &maxiter, wspace);
    ASSERT_EQUAL_INT_OR_FAIL(status, 0, str, "error status from cgls");
    ASSERT_EQUAL_INT_OR_FAIL(maxiter, colsA, str, "wrong number of iterations");
    ASSERT_EQUAL_ARRAY_OR_FAIL(x, x_correct, colsA, tol, str, "cgls solution is not correct");
    for (k = 0; k < colsA; ++k) {
        ASSERT_TRUE_OR_FAIL(fabs(wspace[k]) < 1e-6, str, "too high tolerance");
    }

    if (wspace != NULL) {
        free(wspace);
    }

    SUCCEED(str);
}

bool testCglsTallMatrix(char** str) {
    int k;
    const scs_int rowsA = 10;
    const scs_int colsA = 3;
    const scs_float A[30] = {1.4380, 0.3250, -0.7550, 1.3700, -1.7120, -0.1030,
        -0.2420, 0.3190, 0.3120, -0.8650, -0.0310, -0.1650, 0.6270, 1.0930, 1.1090,
        -0.8640, 0.0770, -1.2150, -1.1140, -0.0070, 1.5320, -0.7700, 0.3710,
        -0.2260, 1.1170, -1.0900, 0.0320, 0.5520, 1.1000, 1.5440};
    const scs_float b[10] = {0.0850, -1.4920, -0.7430, -1.0620, 2.3500, -0.6160,
        0.7480, -0.1930, 0.8880, -0.7650};
    const scs_float x_correct[3] = {-0.465522983317838, 0.027258220607442, 0.386356958159962};

    scs_float x[3] = {1.0, 1.0, 1.0};
    scs_float* wspace;
    scs_float tol = 1e-7;
    scs_int maxiter = 20;
    scs_int status;

    wspace = cgls_malloc_workspace(rowsA, colsA);
    ASSERT_TRUE_OR_FAIL(wspace != NULL, str, "space is NULL");
    status = cgls(rowsA, colsA, A, b, x, tol, &maxiter, wspace);
    ASSERT_EQUAL_INT_OR_FAIL(status, 0, str, "error status");
    ASSERT_EQUAL_INT_OR_FAIL(maxiter, colsA, str, "wrong number of iterations");
    ASSERT_EQUAL_ARRAY_OR_FAIL(x, x_correct, colsA, tol, str, "cgls solution is not correct");
    for (k = 0; k < colsA; ++k) {
        ASSERT_TRUE_OR_FAIL(fabs(wspace[k]) < 1e-12, str, "too high tolerance");
    }

    if (wspace != NULL) {
        free(wspace);
    }

    SUCCEED(str);
}

bool testCglsFatMatrix(char** str) {
    int k;
    const scs_int rowsA = 3;
    const scs_int colsA = 6;
    const scs_float A[] = {0.537, 1.833, -2.259, 0.862, 0.318, -1.308, -0.434, 0.342, 3.578, 2.769, -1.350, 3.034, 0.725, -0.064, 0.714, -0.205, -0.125, 1.489};
    const scs_float b[] = {1.409, 1.417, 0.671};
    const scs_float x_correct[] = {
        0.668689396353836,
        0.872382921069705,
        0.397801374135948,
        0.054759818535695,
        0.677215625688453,
        0.839247578431992
    };
    scs_float x[] = {1., 1., 1., 1., 1., 1.};
    scs_float* wspace;
    scs_float tol = 1e-7;
    scs_int maxiter = 10;
    scs_int status;

    wspace = cgls_malloc_workspace(rowsA, colsA);
    ASSERT_TRUE_OR_FAIL(wspace != NULL, str, "space is NULL");
    status = cgls(rowsA, colsA, A, b, x, tol, &maxiter, wspace);

    ASSERT_EQUAL_INT_OR_FAIL(status, 0, str, "error status");
    ASSERT_EQUAL_INT_OR_FAIL(maxiter, rowsA, str, "wrong number of iterations");
    ASSERT_EQUAL_ARRAY_OR_FAIL(x, x_correct, colsA, tol, str, "cgls solution is not correct");
    for (k = 0; k < colsA; ++k) {
        ASSERT_TRUE_OR_FAIL(fabs(wspace[k]) < 1e-10, str, "too high tolerance");
    }
    if (wspace != NULL) {
        free(wspace);
    }

    SUCCEED(str);
}

bool testQRLSTallMatrix(char** str) {
    scs_int m = 7;
    scs_int n = 3;
    scs_int lwork;
    scs_float * work;
    scs_int status;
    scs_float A[] = {-0.125, -2.542, 0.277, -0.196, -0.197, -0.306, -1.129, 0.194, -0.608, -0.829, 0.535, 0.109, -1.123, 0.046, -1.239, 0.638, 1.145, -0.016, 0.660, -2.546, 0.012};
    scs_float b[] = {-1.0170, -0.1160, -0.7770, -1.1400, 0.3190, -0.5720, -1.6310};
    scs_float x_correct[] = {0.330956315212891, -0.102740136627264, 0.223109442693867};

    lwork = qr_workspace_size(m, n, A, b);

    ASSERT_TRUE_OR_FAIL(lwork > 0, str, "lwork not positive");

    work = malloc(lwork * sizeof (*work));
    ASSERT_TRUE_OR_FAIL(work != NULL, str, "work == NULL");

    status = qrls(m, n, A, b, work, lwork);

    ASSERT_EQUAL_INT_OR_FAIL(status, 0, str, "qrls failed");
    ASSERT_EQUAL_ARRAY_OR_FAIL(b, x_correct, n, 1e-10, str, "wrong solution");


    if (work != NULL) {
        free(work);
    }


    SUCCEED(str);
}