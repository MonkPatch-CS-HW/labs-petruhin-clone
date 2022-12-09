#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mergesort.h"

int comparator_int(const void *a, const void *b)
{
  return *(int *)a - *(int *)b;
}

int comparator_char(const void *a, const void *b)
{
  return (int)(*(char *)a) - *(char *)b;
}

int comparator_str(const void *a, const void *b)
{
  return strcmp(*(char *const *)a, *(char *const *)b);
}

int process_int(int argc, char **argv)
{
  int *arr = malloc((argc - 2) * sizeof(int));
  for (int i = 0; i < argc - 2; i++)
    arr[i] = atoi(argv[i + 2]);
  int res = mergesort(arr, argc - 2, sizeof(int), comparator_int);
  if (res < 0)
  {
    free(arr);
    return res;
  }
  for (int i = 0; i < argc - 2; i++)
    printf("%d%c", arr[i], i == argc - 3 ? '\n' : ' ');
  free(arr);
  return 0;
}

int process_char(int argc, char **argv)
{
  char *arr = malloc((argc - 2) * sizeof(int));
  for (int i = 0; i < argc - 2; i++)
    arr[i] = argv[i + 2][0];
  int res = mergesort(arr, argc - 2, sizeof(char), comparator_char);
  if (res < 0)
  {
    free(arr);
    return res;
  }
  for (int i = 0; i < argc - 2; i++)
    printf("%c%c", arr[i], i == argc - 3 ? '\n' : ' ');
  free(arr);
  return 0;
}

int process_str(int argc, char **argv)
{
  char **arr = malloc((argc - 2) * sizeof(char *));
  for (int i = 0; i < argc - 2; i++)
    arr[i] = argv[i + 2];
  int res = mergesort(arr, argc - 2, sizeof(char *), comparator_str);
  if (res < 0)
  {
    free(arr);
    return res;
  }
  for (int i = 0; i < argc - 2; i++)
    printf("%s%c", arr[i], i == argc - 3 ? '\n' : ' ');
  free(arr);
  return 0;
}

int main(int argc, char **argv)
{
  if (argc < 2)
  {
    printf("incorrect usage\n");
    return 2;
  }
  
  if (argc == 2)
  {
    printf("\n");
    return 0;
  }

  int res = 0;
  if (strcmp(argv[1], "int") == 0)
    res = process_int(argc, argv);
  else if (strcmp(argv[1], "char") == 0)
    res = process_char(argc, argv);
  else if (strcmp(argv[1], "str") == 0)
    res = process_str(argc, argv);
  else
  {
    printf("incorrect type\n");
    return 3;
  }

  if (res < 0)
  {
    printf("Error: memory allocation failed.");
    return 1;
  }
  return 0;
}