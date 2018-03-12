#ifndef LINALG_H_GUARD
#define LINALG_H_GUARD

#ifdef __cplusplus
extern "C" {
#endif

#include "scs.h"
#include <math.h>

#ifdef LAPACK_LIB_FOUND    

    extern void LPCK(gels)(
            const char* trans,
            const blasint* m,
            const blasint* n,
            const blasint* nrhs,
            const scs_float* a,
            const blasint* lda,
            scs_float* b,
            const blasint* ldb,
            scs_float* work,
            blasint* lwork,
            blasint* info);

    extern void LPCK(gelss)(
            const blasint* m,
            const blasint* n,
            const blasint* nrhs,
            const scs_float* A,
            const blasint* lda,
            scs_float* b,
            const blasint* ldb,
            scs_float* S,
            const scs_float* rcond,
            blasint* rank,
            scs_float* work,
            blasint* lwork,
            blasint* info
            );

#define scs_dgels LPCK(gels)
#define scs_dgelss LPCK(gelss)

#endif

    /**
     * \brief Computes the optimal workspace size for ::svdls
     * 
     * @param m     number of rows of matrix A
     * @param n     number of columns of matrix A
     * @return      optimal workspace size
     * 
     * \note To use this function, you need to compile with USE_LAPACK=1 (recommended).
     */
    scs_int svd_workspace_size(
            scs_int m,
            scs_int n
            );

    /**
     * \brief Compute the optimal size of workspace for ::qrls.
     * 
     * @param m rows of A
     * @param n columns of A
     * 
     * @return optimal size of workspace
     * 
     * \note To use this function, you need to compile with USE_LAPACK=1 (recommended).
     */
    scs_int qr_workspace_size(
            scs_int m,
            scs_int n
            );

    /**
     * \brief Solves a least squares problem using the QR factorization
     * 
     * @param m rows of A
     * @param n columns of A
     * @param A On entry, matrix A (column-packed). On exit, if \f$m\geq n\f$, A is 
     *          overwritten by details of its QR factorization as returned by lapack's
     *          DGEQRF; otherwise, A is overwritten by details of its LQ factorization 
     *          as returned by DGELQF.
     * @param b On entry: vector b, On exit: solution
     * @param wspace workspace
     * @param wsize workspace size
     * @return status code (0: success)
     * 
     * @see ::qr_workspace_size
     * 
     * \note This is a wrapper for lapack's ?gels
     * 
     * \warning It is assumed that matrix \f$A\f$ has full rank. If not, 
     * use ::svdls.
     * 
     * \note To use this function, you need to compile with USE_LAPACK=1 (recommended).
     */
    scs_int qrls(
            scs_int m,
            scs_int n,
            scs_float * __restrict A,
            scs_float * __restrict b,
            scs_float * __restrict wspace,
            scs_int wsize
            );

    /**
     * \brief Solves a least squares problem using the SVD factorization
     * 
     * Solves the least squares problem \f$\mathrm{Minimize}\|b-Ax\|^2\f$ where 
     * \f$A\in\mathbb{R}^{m\times n}\f$ and \f$b\in\mathbb{R}^{m}\f$.
     * 
     * @param m                 number of rows of matrix A
     * @param n                 number of columns of matrix A
     * @param A                 On entry, matrix A. On exit, the first min(m,n) 
     *                          rows of A are overwritten with its right singular 
     *                          vectors, stored row-wise.
     * @param b                 On entry, vector b, On exit, solution
     * @param wspace            workspace
     * @param wsize             size of the workspace (its size is returned by #svd_workspace_size)
     * @param rcond             rcond is used to determine the effective rank of A. 
     *                          singular values \f$ \sigma_i \leq \mathrm{rcond} \cdot \sigma_1\f$ 
     *                          are treated as zero.
     * @param singular_values   this function computes the singular values of \f$A\f$
     * @param rank              the effective rank of matrix \f$A\f$, that is, the number 
     *                          of singular values which are greater than 
     *                          \f$\mathrm{rcond} \cdot \sigma_1\f$.
     * @return status (0: success)
     * 
     * \note This is a wrapper for lapack's ?gelss.
     * 
     * \note To use this function, you need to compile with USE_LAPACK=1 (recommended).
     */
    scs_int svdls(
            scs_int m,
            scs_int n,
            scs_float * __restrict A,
            scs_float * __restrict b,
            scs_float * __restrict wspace,
            scs_int wsize,
            scs_float rcond,
            scs_float * __restrict singular_values,
            scs_int * __restrict rank
            );


    /**
     * Performs the operation
     * \f[
     *  x \leftarrow b\cdot a,
     * \f]
     * where \c a is a vector and \c b is a scalar.
     * 
     * @param x
     * @param a
     * @param b
     * @param len
     * 
     * \note with loop unrolling for speed
     */
    void setAsScaledArray(
            scs_float *x,
            const scs_float *a,
            const scs_float b,
            scs_int len);

    /**
     * Performs the operation
     * \f[
     *   a \leftarrow b\cdot a
     * \f]
     * @param a
     * @param b
     * @param len
     * 
     * \note with loop unrolling for speed
     */
    void scaleArray(scs_float *a, const scs_float b, scs_int len);

    /**
     * Computes the inner product of two vectors, that is
     * \f[
     *  \langle x, y \rangle = x'y = \sum_{i=1}^{\mathrm{len}}x_i y_i.
     * \f]
     * @param x
     * @param y
     * @param len
     * @return 
     * 
     * \note with loop unrolling for speed
     */
    scs_float innerProd(const scs_float *x, const scs_float *y, scs_int len);

    /**
     * Returns the square Euclidean norm of a vector.
     * @param v
     * @param len
     * @return 
     * 
     * \note uses ::innerProd
     */
    scs_float calcNormSq(const scs_float *v, scs_int len);

    /**
     * Returns the Euclidean norm of a vector.
     * @param v
     * @param len
     * @return 
     */
    scs_float calcNorm(const scs_float *v, scs_int len);

    /**
     * Returns the infinity norm of a vector.
     * @param a
     * @param l
     * @return 
     */
    scs_float calcNormInf(const scs_float *a, scs_int l);


    /**
     * Performs the operation
     * \f[
     *  a \leftarrow a + \gamma b
     * \f]
     * @param a vector \c a
     * @param b vector \c b
     * @param n length of \c a
     * @param sc the scalar \f$\gamma\f$
     * 
     * \note with loop unrolling for speed
     */
    void addScaledArray(
            scs_float *a,
            const scs_float *b,
            scs_int n,
            const scs_float sc);

    /**
     * Performs the operation
     * \f[
     *  a \leftarrow a + b
     * \f]
     * @param a vector \c a
     * @param b vector \c b
     * @param n length of \c a
     * 
     * \note with loop unrolling for speed
     */
    void addArray(
            scs_float * __restrict a,
            const scs_float * __restrict b,
            scs_int n);

    /**
     * Computes \f$x \leftarrow \alpha u + \beta v\f$
     * 
     * \note The pointer \c x can have the same value as \c u so as to perform
     * operations like \f$x\leftarrow \alpha x + \beta v\f$.     
     */
    void axpy2(
            scs_float *x,
            scs_float * u,
            const scs_float * __restrict v,
            scs_float a,
            scs_float b,
            scs_int n);

    /**
     * Performs the operation
     * \f[
     *  a \leftarrow a - b
     * \f]
     * @param a vector \c a
     * @param b vector \c b
     * @param n length of \c a
     * 
     * \note with loop unrolling for speed
     */
    void subtractArray(scs_float *a, const scs_float *b, scs_int n);

    /**
     * Returns the Euclidean norm of the difference of two vectors
     * @param a
     * @param b
     * @param l
     * @return 
     */
    scs_float calcNormDiff(const scs_float *a, const scs_float *b, scs_int l);

    /**
     * Returns the infinity norm of the difference of two vectors
     * @param a
     * @param b
     * @param l
     * @return 
     */
    scs_float calcNormInfDiff(const scs_float *a, const scs_float *b, scs_int l);


    /**
     * Perofrms the operation
     * \f[
     *    C \leftarrow \beta C + \alpha A B
     * \f]
     * 
     * @param m number of rows of matrix \f$A\f$
     * @param n number of columns of matrix \f$B\f$
     * @param k number of rows of matrix \f$B\f$ (columns of \f$A\f$)
     * @param alpha coefficient \f$\alpha\f$
     * @param A pointer to matrix \f$A\f$
     * @param incRowA increment in traversing the rows of \f$A\f$
     * @param incColA increment in traversing the columns of \f$A\f$
     * @param B pointer to matrix \f$B\f$
     * @param incRowB increment in traversing the rows of \f$B\f$
     * @param incColB increment in traversing the columns of \f$B\f$
     * @param beta coefficient \f$\beta\f$
     * @param C pointer to matrix \f$C\f$
     * @param incRowC increment in traversing the rows of \f$C\f$
     * @param incColC increment in traversing the columns of \f$C\f$
     * 
     * @see ::matrixMultiplicationColumnPacked
     * 
     * \note The implementation of this method is that of 
     * [ULMBLAS](http://apfel.mathematik.uni-ulm.de/~lehn/sghpc/gemm/page13/index.html).
     * 
     * \note The original source code is available at 
     * [this link](http://apfel.mathematik.uni-ulm.de/~lehn/sghpc/gemm/page13/index.html).
     * 
     * \note The [ULMBLAS project](https://github.com/michael-lehn/ulmBLAS) is available
     * on github and is licensed with the 
     * [new BSD licence](https://github.com/michael-lehn/ulmBLAS/blob/master/LICENSE).
     * 
     * \warning This function works only with \c double precision data.
     * 
     */
    void dgemm_nn(
            int m,
            int n,
            int k,
            double alpha,
            const double *A,
            int incRowA,
            int incColA,
            const double *B,
            int incRowB,
            int incColB,
            double beta,
            double *C,
            int incRowC,
            int incColC);

    /**
     * Perofrms the operation \f$C \leftarrow \beta C + \alpha A B,\f$
     * where \f$A\f$, \f$B\f$ and \f$C\f$ are column-packed matrices.
     * 
     * This method is a proxy to ::dgemm_nn.
     * 
     * @param m number of rows of matrix \f$A\f$
     * @param n number of columns of matrix \f$B\f$
     * @param k number of rows of matrix \f$B\f$ (columns of \f$A\f$)
     * @param alpha coefficient \f$\alpha\f$
     * @param A pointer to matrix \f$A\f$ in column-packed form
     * @param beta coefficient \f$\beta\f$
     * @param B pointer to matrix \f$B\f$ in column-packed form
     * @param C pointer to matrix \f$C\f$ in column-packed form
     * 
     * @see ::dgemm_nn
     * 
     * \note This is a wrapper for #dgemm_nn
     */
    void matrixMultiplicationColumnPacked(
            int m,
            int n,
            int k,
            double alpha,
            const double *A,
            double beta,
            const double *B,
            double *C);

    /**
     * Perofrms the operation \f$C \leftarrow \beta C + \alpha A^{\top} B,\f$
     * where \f$A\f$, \f$B\f$ and \f$C\f$ are column-packed matrices.
     * 
     * This method is a proxy to ::dgemm_nn.
     * 
     * @param m number of rows of matrix \f$A^\top\f$
     * @param n number of columns of matrix \f$B\f$
     * @param k number of rows of matrix \f$B\f$ (columns of \f$A^\top\f$)
     * @param alpha coefficient \f$\alpha\f$
     * @param A pointer to matrix \f$A\f$ in column-packed form
     * @param beta coefficient \f$\beta\f$
     * @param B pointer to matrix \f$B\f$ in column-packed form
     * @param C pointer to matrix \f$C\f$ in column-packed form
     * 
     * @see ::dgemm_nn
     * 
     * \note This is a wrapper for #dgemm_nn
     */
    void matrixMultiplicationTransColumnPacked(
            int m,
            int n,
            int k,
            double alpha,
            const double *A,
            double beta,
            const double *B,
            double *C);

    /**
     * Computes the sum \f$S = \sum_i x_i\f$ of a given array \f$x\f$
     * 
     * @param x given array
     * @param len length of array
     * @return sum
     */
    scs_float sumArray(
            const scs_float *__restrict x,
            scs_int len);


    /** 
     * Allocates memory to be used as workspace in #cgls (see documentation of #cgls
     * for details).
     * 
     * If either \c m or \c n are negative or zero, it returns #SCS_NULL.
     * 
     * \note The caller should always check whether the returned pointer is #SCS_NULL.
     * 
     * \warning The caller should free the memory allocated by this function. Example:
     * ~~~~~
     * scs_int m = 10;
     * scs_int n = 2;
     * scs_float * ws;
     * ws = cgls_malloc_workspace(scs_int m, scs_int n);
     * if (ws == SCS_NULL) {
     *      // memory not allocated, take necessary action
     * }
     * // use ws in cgls
     * scs_free(ws);
     * ~~~~~
     * 
     * @param m     number of rows of matrix A
     * @param n     number of columns of matrix A
     * @return      pointer to allocated 
     * 
     * @see #cgls
     */
    scs_float * cgls_malloc_workspace(scs_int m, scs_int n);

    /**
     * Solves a least squares problem using the conjugate gradient method.
     * 
     * Solves the problem: Minimize \f$\|Ax-b\|^2\f$, or, what is the same, the 
     * linear system \f$ A^{\top}Ax = A^{\top}b\f$.
     * 
     * The iterations are terminated when the Euclidean norm of the residual, 
     * \f$r = A^{\top}(b - Ax)\f$
     * becomes smaller than the specified tolerance.
     *   
     * @param m         Number of rows of matrix A
     * @param n         Number of columns of A
     * @param A         Matrix A (column-packed)
     * @param b         Right-hand side vector b
     * @param x         Solution (on entry: initial guess)
     * @param tol       Tolerance
     * @param maxiter   Maximum number of CG iterations (on exit: number of iterations)
     * @param wspace    Externally allocated memory space serving as workspace. 
     *                  This must be of size <code>(max(m,n) + m + 2 * n) * sizeof(scs_float)</code>.
     *                  On exit, the first \c n memory positions store the residual.
     *                  You may use #cgls_malloc_workspace to allocate the workspace.
     * 
     * @return status code (0: success, 1: maximum number of iterations reached).
     * 
     * @see ::cgls_malloc_workspace
     */
    scs_int cgls(
            scs_int m,
            scs_int n,
            const scs_float * __restrict A,
            const scs_float * __restrict b,
            scs_float*__restrict x,
            scs_float tol,
            scs_int*__restrict maxiter,
            scs_float *__restrict wspace
            );


#ifdef __cplusplus
}
#endif
#endif
