#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "mergesort.h"

int merge(
    void *array,
    size_t mid,
    size_t elements, size_t element_size,
    int (*comparator)(const void *, const void *))
{
  if (elements <= 1)
    return 0;
  void *pivot = (char *)array + element_size * mid;
  void *end = (char *)array + element_size * elements;
  void *out = malloc(elements * element_size);
  if (out == NULL)
    return -1;
  void *l = array, *r = pivot, *o = out;

  while (l < pivot || r < end)
  {
    int append_l = l < pivot && (r >= end || comparator(l, r) <= 0);
    void **part = append_l ? &l : &r;
    for (size_t i = 0; i < element_size; i++)
      *(char *)o++ = *(char *)(*part)++;
  }
  memcpy(array, out, element_size * elements);
  free(out);
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