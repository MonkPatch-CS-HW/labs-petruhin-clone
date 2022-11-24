#include <stddef.h>
#include "str.h"

char *my_strcpy(char *destination, const char *source)
{
  char *pointer = destination;
  while ((*pointer++ = *source++))
    ;
  return destination;
}

char *my_strcat(char *destination, const char *source)
{
  char *pointer = destination;
  while ((*pointer++))
    ;
  --pointer;
  while ((*pointer++ = *source++))
    ;
  return destination;
}

int my_strcmp(const char *str1, const char *str2)
{
  while ((*str1++ == *str2++) && *(str1 - 1))
    ;
  return *--str1 - *--str2;
}

size_t my_strlen(const char *str)
{
  const char *pointer = str;
  while ((*pointer++))
    ;
  return (pointer - 1) - str;
}