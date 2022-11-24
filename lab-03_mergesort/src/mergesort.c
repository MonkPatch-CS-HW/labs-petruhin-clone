#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "mergesort.h"

void my_memcpy(void *dest, void *src, size_t n)
{
  char *d = (char *)dest;
  char *s = (char *)src;
  while (n--)
    *d++ = *s++;
}

int merge(
    void *array,
    size_t pivot_index,
    size_t elements, size_t element_size,
    int (*comparator)(const void *, const void *))
{
  if (elements <= 1)
    return 0;
  void *arr_pivot = (char *)array + element_size * pivot_index;
  void *arr_end = (char *)array + element_size * elements;
  void *out_arr = malloc(elements * element_size);
  if (out_arr == NULL)
    return -1;
  void *l = array, *r = arr_pivot, *out_ptr = out_arr;

  while (l < arr_pivot || r < arr_end)
  {
    int append_l = l < arr_pivot && (r >= arr_end || comparator(l, r) <= 0);
    void **part = append_l ? &l : &r;
    my_memcpy(out_ptr, *part, element_size);
    out_ptr = (char *)out_ptr + element_size;
    *part = *(char **)part + element_size;
  }
  my_memcpy(array, out_arr, element_size * elements);
  free(out_arr);
  return 0;
}

int mergesort(
    void *array,
    size_t elements, size_t element_size,
    int (*comparator)(const void *, const void *))
{
  if (elements < 2)
    return 0;
  size_t mid = elements / 2;
  int res;
  if ((res = mergesort(array, mid, element_size, comparator)) < 0)
    return res;
  if ((res = mergesort((char *)array + mid * element_size, elements - mid, element_size, comparator)) < 0)
    return res;
  if ((res = merge(array, mid, elements, element_size, comparator)) < 0)
    return res;
  return res;
}