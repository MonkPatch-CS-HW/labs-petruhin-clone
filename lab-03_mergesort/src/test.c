#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "mergesort.h"

int reverse_int_comparator(const void *a, const void *b)
{
  return *(int *)b - *(int *)a;
}

void test_mergesort()
{
  int arr[] = {1, -2, 3, -400, 500, 0};
  int ans[] = {-400, -2, 0, 1, 3, 500};
  mergesort(arr, 6, sizeof(int), reverse_int_comparator);
  assert(memcmp(arr, ans, 6 * sizeof(int)) == 0);
}

int main()
{
  test_mergesort();
  return 0;
}