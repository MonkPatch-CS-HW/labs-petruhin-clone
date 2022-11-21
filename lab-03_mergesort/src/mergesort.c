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
    if ((l < pivot && r == end) || (l < pivot && comparator(l, r) <= 0))
    {
      memcpy(o, l, element_size);
      l = (char *)l + element_size;
    }
    else if ((l == pivot && r < end) || (r < end && comparator(l, r) >= 0))
    {
      memcpy(o, r, element_size);
      r = (char *)r + element_size;
    }
    o = (char *)o + element_size;
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