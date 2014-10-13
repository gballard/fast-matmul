#include <chrono>
#include <iostream>
#include <mkl.h>

void Dgemm(double *A, double *B, double *C, int N) {
  int M = N; int K = N;
  double alpha = 1.0;  double beta = 0.0;
  int lda = N;  int ldb = N;  int ldc = N;
  DGEMM("N", "N", &M, &N, &K, &alpha, A, &lda, B, &ldb, &beta, C, &ldc);
}

int main() {
  int N = 8000;
  double *A = new double[N * N];
  double *B = new double[N * N];
  double *C = new double[N * N];

  auto start = std::chrono::high_resolution_clock::now();  
  Dgemm(A, B, C, N);
  auto end = std::chrono::high_resolution_clock::now();
  auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
  std::cout << diff.count() << " ms" << std::endl;
}
