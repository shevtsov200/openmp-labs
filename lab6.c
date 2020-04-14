#include<omp.h>

#include <stdbool.h>

#include<time.h>

#include<stdio.h>

int A[99999999];

bool isPrime(int n) {
  if (n <= 1) {
    return false;
  }

  for (int i = 2; i < n; i++) {
    if (n % i == 0) {
      return false;
    }
  }

  return true;
}

int justCount(int n) {
  int i;
  double sum = 0.0;

  int a2 = 0;

  for (i = 0; i < n; ++i) {
    a2 = A[i];
    if (isPrime(a2)) {
      sum = sum + a2;
    }
  }

  return sum;
}

int countInParallel(int n) {
  int i;
  double sum = 0.0;

  if (omp_get_max_threads() < 4) {
    printf("not enough threads");
    getch();

    return (0);
  } else {
    omp_set_num_threads(4);
  }

  int a2 = 0;

  #pragma omp parallel for schedule(static, 25) private(i, a2)\
  shared(A) reduction(+: sum)
  for (i = 0; i < n; ++i) {
    a2 = A[i];
    if (isPrime(a2)) {
      sum = sum + a2;
    }
  }

  return sum;
}

int main() {
  int n = sizeof(A) / sizeof(A[0]);
  double sum = 0.0;
  int i;

  #pragma omp parallel for shared(A)
  for (i = 0; i < n; ++i) {
    A[i] = 2;
  }

  printf("start just count\n");
  clock_t begin = clock();

  sum = justCount(n);

  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("just count time = %f\n", time_spent);

  printf("start count in parallel\n");
  begin = clock();
  sum = countInParallel(n);
  end = clock();
  time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("count in parallel time = %f\n", time_spent);

  return (0);
}