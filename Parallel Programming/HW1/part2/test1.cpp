#include <iostream>
#include "test.h"
#include "fasttime.h"
#include <x86intrin.h>

void __attribute__((aligned(16))) test1(float* __restrict  a, float* __restrict b, float* __restrict c, int N) {
  __builtin_assume(N == 1024);
  a = (float *)__builtin_assume_aligned(a, 32);
  b = (float *)__builtin_assume_aligned(b, 32);
  c = (float *)__builtin_assume_aligned(c, 32);
  fasttime_t time1 = gettime();
  // #pragma vector aligned
  
  for (int i=0; i<I; i++) {
    for (int j=0; j<N; j++) {
      c[j] = a[j] + b[j];
    }
  }
  
  //  __m256 qa, qb, qc;
  // for (int i=0; i<I; i++) {
  //   for(int j =0;j<N/8;j++){
  //     qa = _mm256_load_ps(a);
  //     qb = _mm256_load_ps(b);
  //     qc = _mm256_load_ps(c);
  //     qc = _mm256_add_ps(qa, qb);
  //     _mm256_store_ps(c, qc);
  //     a += 8;
  //     b += 8;
  //     c += 8;
  //    }
  //    a-=N;
  //    b-=N;
  //    c-=N;
  // }
  // #pragma ivdep
  // #pragma vector align
  // #pragma vector aligned
  // #pragma omp simd aligned(a:16,b:16,c:16)
  
  fasttime_t time2 = gettime();

  double elapsedf = tdiff(time1, time2);
  std::cout << "Elapsed execution time of the loop in test1():\n" 
    << elapsedf << "sec (N: " << N << ", I: " << I << ")\n";
}