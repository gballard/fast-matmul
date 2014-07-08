#ifndef _grey432_20_144_HPP_
#define _grey432_20_144_HPP_


// This is an automatically generated file from gen.py.
#include "common.hpp"


namespace grey432_20_144 {
template <typename Scalar>
void FastMatmul(Matrix<Scalar>& A, Matrix<Scalar>& B, Matrix<Scalar>& C, int numsteps, double x=1e-8) {
    // Update multipliers
    C.UpdateMultiplier(A.multiplier());
    C.UpdateMultiplier(B.multiplier());
    A.UpdateMultiplier(Scalar(1.0));
    B.UpdateMultiplier(Scalar(1.0));
    // Base case for recursion
    if (numsteps == 0) {
        Gemm(A, B, C);
        return;
    }

    int A_row_step = A.m() / 4;
    int A_col_step = A.n() / 3;
    Matrix<Scalar> A11 = A.Subblock(4, 3, 1, 1);
    Matrix<Scalar> A12 = A.Subblock(4, 3, 1, 2);
    Matrix<Scalar> A13 = A.Subblock(4, 3, 1, 3);
    Matrix<Scalar> A21 = A.Subblock(4, 3, 2, 1);
    Matrix<Scalar> A22 = A.Subblock(4, 3, 2, 2);
    Matrix<Scalar> A23 = A.Subblock(4, 3, 2, 3);
    Matrix<Scalar> A31 = A.Subblock(4, 3, 3, 1);
    Matrix<Scalar> A32 = A.Subblock(4, 3, 3, 2);
    Matrix<Scalar> A33 = A.Subblock(4, 3, 3, 3);
    Matrix<Scalar> A41 = A.Subblock(4, 3, 4, 1);
    Matrix<Scalar> A42 = A.Subblock(4, 3, 4, 2);
    Matrix<Scalar> A43 = A.Subblock(4, 3, 4, 3);
    int B_row_step = B.m() / 3;
    int B_col_step = B.n() / 2;
    Matrix<Scalar> B11 = B.Subblock(3, 2, 1, 1);
    Matrix<Scalar> B12 = B.Subblock(3, 2, 1, 2);
    Matrix<Scalar> B21 = B.Subblock(3, 2, 2, 1);
    Matrix<Scalar> B22 = B.Subblock(3, 2, 2, 2);
    Matrix<Scalar> B31 = B.Subblock(3, 2, 3, 1);
    Matrix<Scalar> B32 = B.Subblock(3, 2, 3, 2);
    int C_row_step = C.m() / 4;
    int C_col_step = C.n() / 2;
    Matrix<Scalar> C11 = C.Subblock(4, 2, 1, 1);
    Matrix<Scalar> C12 = C.Subblock(4, 2, 1, 2);
    Matrix<Scalar> C21 = C.Subblock(4, 2, 2, 1);
    Matrix<Scalar> C22 = C.Subblock(4, 2, 2, 2);
    Matrix<Scalar> C31 = C.Subblock(4, 2, 3, 1);
    Matrix<Scalar> C32 = C.Subblock(4, 2, 3, 2);
    Matrix<Scalar> C41 = C.Subblock(4, 2, 4, 1);
    Matrix<Scalar> C42 = C.Subblock(4, 2, 4, 2);


    // These are the intermediate matrices.
    // We define them here so that they can be used
    // inside the lambda functions for Cilk.
    Matrix<Scalar> M1(C_row_step, C_col_step, C.multiplier());
    Matrix<Scalar> M2(C_row_step, C_col_step, C.multiplier());
    Matrix<Scalar> M3(C_row_step, C_col_step, C.multiplier());
    Matrix<Scalar> M4(C_row_step, C_col_step, C.multiplier());
    Matrix<Scalar> M5(C_row_step, C_col_step, C.multiplier());
    Matrix<Scalar> M6(C_row_step, C_col_step, C.multiplier());
    Matrix<Scalar> M7(C_row_step, C_col_step, C.multiplier());
    Matrix<Scalar> M8(C_row_step, C_col_step, C.multiplier());
    Matrix<Scalar> M9(C_row_step, C_col_step, C.multiplier());
    Matrix<Scalar> M10(C_row_step, C_col_step, C.multiplier());
    Matrix<Scalar> M11(C_row_step, C_col_step, C.multiplier());
    Matrix<Scalar> M12(C_row_step, C_col_step, C.multiplier());
    Matrix<Scalar> M13(C_row_step, C_col_step, C.multiplier());
    Matrix<Scalar> M14(C_row_step, C_col_step, C.multiplier());
    Matrix<Scalar> M15(C_row_step, C_col_step, C.multiplier());
    Matrix<Scalar> M16(C_row_step, C_col_step, C.multiplier());
    Matrix<Scalar> M17(C_row_step, C_col_step, C.multiplier());
    Matrix<Scalar> M18(C_row_step, C_col_step, C.multiplier());
    Matrix<Scalar> M19(C_row_step, C_col_step, C.multiplier());
    Matrix<Scalar> M20(C_row_step, C_col_step, C.multiplier());


#ifdef _OPEN_MP_
    #pragma omp parallel
    {
    #pragma omp single
        {
#endif
    // M1 = (1.0 * A11) * (-1.0 * B11 + 1.0 * B21)
#ifdef _CILK_
    cilk_spawn [&] {
#elif defined _OPEN_MP_
# pragma omp task
    {
#endif
    Matrix<Scalar> M1B(B11.m(), B11.n());
    Add(B11, B21, Scalar(-1.0), Scalar(1.0), M1B);
    FastMatmul(A11, M1B, M1, numsteps - 1, x);
    M1B.deallocate();
#ifdef _CILK_
    }();
#elif defined _OPEN_MP_
    }
#endif

    // M2 = (1.0 * A21 + 1.0 * A22) * (-1.0 * B22 + 1.0 * B32)
#ifdef _CILK_
    cilk_spawn [&] {
#elif defined _OPEN_MP_
# pragma omp task
    {
#endif
    Matrix<Scalar> M2A(A11.m(), A11.n());
    Add(A21, A22, Scalar(1.0), Scalar(1.0), M2A);
    Matrix<Scalar> M2B(B11.m(), B11.n());
    Add(B22, B32, Scalar(-1.0), Scalar(1.0), M2B);
    FastMatmul(M2A, M2B, M2, numsteps - 1, x);
    M2A.deallocate();
    M2B.deallocate();
#ifdef _CILK_
    }();
#elif defined _OPEN_MP_
    }
#endif

    // M3 = (1.0 * A11 + 1.0 * A12 + 1.0 * A13) * (-1.0 * B31)
#ifdef _CILK_
    cilk_spawn [&] {
#elif defined _OPEN_MP_
# pragma omp task
    {
#endif
    Matrix<Scalar> M3A(A11.m(), A11.n());
    Add(A11, A12, A13, Scalar(1.0), Scalar(1.0), Scalar(1.0), M3A);
    M3.UpdateMultiplier(Scalar(-1));
    FastMatmul(M3A, B31, M3, numsteps - 1, x);
    M3A.deallocate();
#ifdef _CILK_
    }();
#elif defined _OPEN_MP_
    }
#endif

    // M4 = (-1.0 * A11 + -1.0 * A12 + -1.0 * A43) * (-1.0 * B21 + 1.0 * B22 + 1.0 * B31)
#ifdef _CILK_
    cilk_spawn [&] {
#elif defined _OPEN_MP_
# pragma omp task
    {
#endif
    Matrix<Scalar> M4A(A11.m(), A11.n());
    Add(A11, A12, A43, Scalar(-1.0), Scalar(-1.0), Scalar(-1.0), M4A);
    Matrix<Scalar> M4B(B11.m(), B11.n());
    Add(B21, B22, B31, Scalar(-1.0), Scalar(1.0), Scalar(1.0), M4B);
    FastMatmul(M4A, M4B, M4, numsteps - 1, x);
    M4A.deallocate();
    M4B.deallocate();
#ifdef _CILK_
    }();
#elif defined _OPEN_MP_
    }
#endif

    // M5 = (-1.0 * A43) * (-1.0 * B21 + 1.0 * B22 + 1.0 * B31 + -1.0 * B32)
#ifdef _CILK_
    cilk_spawn [&] {
#elif defined _OPEN_MP_
# pragma omp task
    {
#endif
    Matrix<Scalar> M5B(B11.m(), B11.n());
    Add(B21, B22, B31, B32, Scalar(-1.0), Scalar(1.0), Scalar(1.0), Scalar(-1.0), M5B);
    M5.UpdateMultiplier(Scalar(-1));
    FastMatmul(A43, M5B, M5, numsteps - 1, x);
    M5B.deallocate();
#ifdef _CILK_
    }();
#elif defined _OPEN_MP_
    }
#endif

    // M6 = (1.0 * A32 + 1.0 * A33 + -1.0 * A41) * (1.0 * B11 + 1.0 * B22)
#ifdef _CILK_
    cilk_spawn [&] {
#elif defined _OPEN_MP_
# pragma omp task
    {
#endif
    Matrix<Scalar> M6A(A11.m(), A11.n());
    Add(A32, A33, A41, Scalar(1.0), Scalar(1.0), Scalar(-1.0), M6A);
    Matrix<Scalar> M6B(B11.m(), B11.n());
    Add(B11, B22, Scalar(1.0), Scalar(1.0), M6B);
    FastMatmul(M6A, M6B, M6, numsteps - 1, x);
    M6A.deallocate();
    M6B.deallocate();
#ifdef _CILK_
    }();
#elif defined _OPEN_MP_
    }
#endif

    // M7 = (1.0 * A11 + -1.0 * A21) * (1.0 * B12 + -1.0 * B22 + 1.0 * B32)
#ifdef _CILK_
    cilk_spawn [&] {
#elif defined _OPEN_MP_
# pragma omp task
    {
#endif
    Matrix<Scalar> M7A(A11.m(), A11.n());
    Add(A11, A21, Scalar(1.0), Scalar(-1.0), M7A);
    Matrix<Scalar> M7B(B11.m(), B11.n());
    Add(B12, B22, B32, Scalar(1.0), Scalar(-1.0), Scalar(1.0), M7B);
    FastMatmul(M7A, M7B, M7, numsteps - 1, x);
    M7A.deallocate();
    M7B.deallocate();
#ifdef _CILK_
    }();
#elif defined _OPEN_MP_
    }
#endif

    // M8 = (1.0 * A33) * (-1.0 * B21 + 1.0 * B31)
#ifdef _CILK_
    cilk_spawn [&] {
#elif defined _OPEN_MP_
# pragma omp task
    {
#endif
    Matrix<Scalar> M8B(B11.m(), B11.n());
    Add(B21, B31, Scalar(-1.0), Scalar(1.0), M8B);
    FastMatmul(A33, M8B, M8, numsteps - 1, x);
    M8B.deallocate();
#ifdef _CILK_
    }();
#elif defined _OPEN_MP_
    }
#endif

    // M9 = (1.0 * A21 + 1.0 * A22 + -1.0 * A31 + 1.0 * A33 + 1.0 * A41) * (-1.0 * B11 + 1.0 * B12)
#ifdef _CILK_
    cilk_spawn [&] {
#elif defined _OPEN_MP_
# pragma omp task
    {
#endif
    Matrix<Scalar> M9A(A11.m(), A11.n());
    Add(A21, A22, A31, A33, A41, Scalar(1.0), Scalar(1.0), Scalar(-1.0), Scalar(1.0), Scalar(1.0), M9A);
    Matrix<Scalar> M9B(B11.m(), B11.n());
    Add(B11, B12, Scalar(-1.0), Scalar(1.0), M9B);
    FastMatmul(M9A, M9B, M9, numsteps - 1, x);
    M9A.deallocate();
    M9B.deallocate();
#ifdef _CILK_
    }();
#elif defined _OPEN_MP_
    }
#endif

    // M10 = (-1.0 * A11 + -1.0 * A12 + -1.0 * A41 + 1.0 * A42) * (1.0 * B22)
#ifdef _CILK_
    cilk_spawn [&] {
#elif defined _OPEN_MP_
# pragma omp task
    {
#endif
    Matrix<Scalar> M10A(A11.m(), A11.n());
    Add(A11, A12, A41, A42, Scalar(-1.0), Scalar(-1.0), Scalar(-1.0), Scalar(1.0), M10A);
    FastMatmul(M10A, B22, M10, numsteps - 1, x);
    M10A.deallocate();
#ifdef _CILK_
    }();
#elif defined _OPEN_MP_
    }
#endif

    // M11 = (-1.0 * A32 + -1.0 * A33 + 1.0 * A42 + 1.0 * A43) * (-1.0 * B21 + 1.0 * B22)
#ifdef _CILK_
    cilk_spawn [&] {
#elif defined _OPEN_MP_
# pragma omp task
    {
#endif
    Matrix<Scalar> M11A(A11.m(), A11.n());
    Add(A32, A33, A42, A43, Scalar(-1.0), Scalar(-1.0), Scalar(1.0), Scalar(1.0), M11A);
    Matrix<Scalar> M11B(B11.m(), B11.n());
    Add(B21, B22, Scalar(-1.0), Scalar(1.0), M11B);
    FastMatmul(M11A, M11B, M11, numsteps - 1, x);
    M11A.deallocate();
    M11B.deallocate();
#ifdef _CILK_
    }();
#elif defined _OPEN_MP_
    }
#endif

    // M12 = (-1.0 * A21 + -1.0 * A22 + -1.0 * A33) * (-1.0 * B11 + 1.0 * B12 + -1.0 * B22 + 1.0 * B32)
#ifdef _CILK_
    cilk_spawn [&] {
#elif defined _OPEN_MP_
# pragma omp task
    {
#endif
    Matrix<Scalar> M12A(A11.m(), A11.n());
    Add(A21, A22, A33, Scalar(-1.0), Scalar(-1.0), Scalar(-1.0), M12A);
    Matrix<Scalar> M12B(B11.m(), B11.n());
    Add(B11, B12, B22, B32, Scalar(-1.0), Scalar(1.0), Scalar(-1.0), Scalar(1.0), M12B);
    FastMatmul(M12A, M12B, M12, numsteps - 1, x);
    M12A.deallocate();
    M12B.deallocate();
#ifdef _CILK_
    }();
#elif defined _OPEN_MP_
    }
#endif

    // M13 = (1.0 * A41) * (1.0 * B12 + 1.0 * B22)
#ifdef _CILK_
    cilk_spawn [&] {
#elif defined _OPEN_MP_
# pragma omp task
    {
#endif
    Matrix<Scalar> M13B(B11.m(), B11.n());
    Add(B12, B22, Scalar(1.0), Scalar(1.0), M13B);
    FastMatmul(A41, M13B, M13, numsteps - 1, x);
    M13B.deallocate();
#ifdef _CILK_
    }();
#elif defined _OPEN_MP_
    }
#endif

    // M14 = (-1.0 * A31 + 1.0 * A32 + 1.0 * A33) * (-1.0 * B11)
#ifdef _CILK_
    cilk_spawn [&] {
#elif defined _OPEN_MP_
# pragma omp task
    {
#endif
    Matrix<Scalar> M14A(A11.m(), A11.n());
    Add(A31, A32, A33, Scalar(-1.0), Scalar(1.0), Scalar(1.0), M14A);
    M14.UpdateMultiplier(Scalar(-1));
    FastMatmul(M14A, B11, M14, numsteps - 1, x);
    M14A.deallocate();
#ifdef _CILK_
    }();
#elif defined _OPEN_MP_
    }
#endif

    // M15 = (-1.0 * A11 + 1.0 * A13 + -1.0 * A22 + -1.0 * A23 + -1.0 * A43) * (1.0 * B32)
#ifdef _CILK_
    cilk_spawn [&] {
#elif defined _OPEN_MP_
# pragma omp task
    {
#endif
    Matrix<Scalar> M15A(A11.m(), A11.n());
    Add(A11, A13, A22, A23, A43, Scalar(-1.0), Scalar(1.0), Scalar(-1.0), Scalar(-1.0), Scalar(-1.0), M15A);
    FastMatmul(M15A, B32, M15, numsteps - 1, x);
    M15A.deallocate();
#ifdef _CILK_
    }();
#elif defined _OPEN_MP_
    }
#endif

    // M16 = (1.0 * A32 + 1.0 * A33) * (-1.0 * B11 + -1.0 * B21)
#ifdef _CILK_
    cilk_spawn [&] {
#elif defined _OPEN_MP_
# pragma omp task
    {
#endif
    Matrix<Scalar> M16A(A11.m(), A11.n());
    Add(A32, A33, Scalar(1.0), Scalar(1.0), M16A);
    Matrix<Scalar> M16B(B11.m(), B11.n());
    Add(B11, B21, Scalar(-1.0), Scalar(-1.0), M16B);
    FastMatmul(M16A, M16B, M16, numsteps - 1, x);
    M16A.deallocate();
    M16B.deallocate();
#ifdef _CILK_
    }();
#elif defined _OPEN_MP_
    }
#endif

    // M17 = (-1.0 * A23 + 1.0 * A33) * (-1.0 * B11 + 1.0 * B12 + 1.0 * B21 + -1.0 * B22 + -1.0 * B31 + 1.0 * B32)
#ifdef _CILK_
    cilk_spawn [&] {
#elif defined _OPEN_MP_
# pragma omp task
    {
#endif
    Matrix<Scalar> M17A(A11.m(), A11.n());
    Add(A23, A33, Scalar(-1.0), Scalar(1.0), M17A);
    Matrix<Scalar> M17B(B11.m(), B11.n());
    Add(B11, B12, B21, B22, B31, B32, Scalar(-1.0), Scalar(1.0), Scalar(1.0), Scalar(-1.0), Scalar(-1.0), Scalar(1.0), M17B);
    FastMatmul(M17A, M17B, M17, numsteps - 1, x);
    M17A.deallocate();
    M17B.deallocate();
#ifdef _CILK_
    }();
#elif defined _OPEN_MP_
    }
#endif

    // M18 = (-1.0 * A11 + -1.0 * A22 + -1.0 * A23) * (1.0 * B11 + -1.0 * B12 + -1.0 * B21 + 1.0 * B22 + -1.0 * B32)
#ifdef _CILK_
    cilk_spawn [&] {
#elif defined _OPEN_MP_
# pragma omp task
    {
#endif
    Matrix<Scalar> M18A(A11.m(), A11.n());
    Add(A11, A22, A23, Scalar(-1.0), Scalar(-1.0), Scalar(-1.0), M18A);
    Matrix<Scalar> M18B(B11.m(), B11.n());
    Add(B11, B12, B21, B22, B32, Scalar(1.0), Scalar(-1.0), Scalar(-1.0), Scalar(1.0), Scalar(-1.0), M18B);
    FastMatmul(M18A, M18B, M18, numsteps - 1, x);
    M18A.deallocate();
    M18B.deallocate();
#ifdef _CILK_
    }();
#elif defined _OPEN_MP_
    }
#endif

    // M19 = (1.0 * A11 + 1.0 * A12) * (-1.0 * B21 + 1.0 * B31)
#ifdef _CILK_
    cilk_spawn [&] {
#elif defined _OPEN_MP_
# pragma omp task
    {
#endif
    Matrix<Scalar> M19A(A11.m(), A11.n());
    Add(A11, A12, Scalar(1.0), Scalar(1.0), M19A);
    Matrix<Scalar> M19B(B11.m(), B11.n());
    Add(B21, B31, Scalar(-1.0), Scalar(1.0), M19B);
    FastMatmul(M19A, M19B, M19, numsteps - 1, x);
    M19A.deallocate();
    M19B.deallocate();
#ifdef _CILK_
    }();
#elif defined _OPEN_MP_
    }
#endif

    // M20 = (1.0 * A22 + 1.0 * A23) * (-1.0 * B11 + 1.0 * B12 + 1.0 * B21 + -1.0 * B22)
#ifdef _CILK_
    cilk_spawn [&] {
#elif defined _OPEN_MP_
# pragma omp task
    {
#endif
    Matrix<Scalar> M20A(A11.m(), A11.n());
    Add(A22, A23, Scalar(1.0), Scalar(1.0), M20A);
    Matrix<Scalar> M20B(B11.m(), B11.n());
    Add(B11, B12, B21, B22, Scalar(-1.0), Scalar(1.0), Scalar(1.0), Scalar(-1.0), M20B);
    FastMatmul(M20A, M20B, M20, numsteps - 1, x);
    M20A.deallocate();
    M20B.deallocate();
#ifdef _CILK_
    }();
#elif defined _OPEN_MP_
    }
#endif

#ifdef _CILK_
    cilk_sync;
#elif defined _OPEN_MP_
        }  // End omp single region
    }  // End omp parallel region
#endif


    Add(M1, M3, M19, Scalar(-1.0), Scalar(-1.0), Scalar(-1.0), C11);
    Add(M1, M4, M5, M15, M18, M19, M20, Scalar(-1.0), Scalar(-1.0), Scalar(1.0), Scalar(1.0), Scalar(1.0), Scalar(-1.0), Scalar(-1.0), C12);
    Add(M1, M7, M8, M12, M17, M18, Scalar(-1.0), Scalar(-1.0), Scalar(1.0), Scalar(1.0), Scalar(1.0), Scalar(1.0), C21);
    Add(M1, M2, M7, M18, M20, Scalar(-1.0), Scalar(-1.0), Scalar(-1.0), Scalar(1.0), Scalar(-1.0), C22);
    Add(M8, M14, M16, Scalar(1.0), Scalar(1.0), Scalar(-1.0), C31);
    Add(M2, M6, M9, M12, M13, M14, Scalar(-1.0), Scalar(1.0), Scalar(-1.0), Scalar(-1.0), Scalar(1.0), Scalar(1.0), C32);
    Add(M4, M6, M10, M11, M16, M19, Scalar(-1.0), Scalar(-1.0), Scalar(1.0), Scalar(-1.0), Scalar(-1.0), Scalar(-1.0), C41);
    Add(M4, M5, M10, M13, M19, Scalar(-1.0), Scalar(1.0), Scalar(1.0), Scalar(1.0), Scalar(-1.0), C42);


    // Handle edge cases with dynamic peeling
    DynamicPeeling(A, B, C, 4, 3, 2);
}

}
  // namespace grey432_20_144
#endif  // _grey432_20_144_HPP_