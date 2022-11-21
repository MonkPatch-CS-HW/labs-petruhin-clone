#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "mergesort.h"

void merge(
    void *array,
    size_t mid,
    size_t elements, size_t element_size,
    int (*comparator)(const void *, const void *))
{
  if (elements <= 1)
    return;
  void *pivot = (char *)array + element_size * mid;
  void *end = (char *)array + element_size * elements;
  void *out = malloc(elements * element_size);
  void *l = array, *r = pivot, *o = out;

  while (l < pivot || r < end)
  {
    int append_l = l < pivot && (r >= end || comparator(l, r) <= 0);
    void **part = append_l ? &l : &r;
    for (size_t i = 0; i < element_size; i++)
      *(char*)o++ = *(char*)(*part)++;
  }
  memcpy(array, out, element_size * elements);
  free(out);
}

void mergesort(
    void *array,
    size_t elements, size_t element_size,
    int (*comparator)(const void *, const void *))
{
  if (elements < 2)
    return;
  size_t mid = elements / 2;
  mergesort(array, mid, element_size, comparator);
  mergesort((char *)array + mid * element_size, elements - mid, element_size, comparator);
  merge(array, mid, elements, element_size, comparator);
}