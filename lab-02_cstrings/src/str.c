#include <stddef.h>

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
  while ((*(pointer++ - 1) = *source++))
    ;
  return destination;
}

int my_strcmp(const char *str1, const char *str2)
{
  do
  {
    if (*str1 < *str2)
      return -1;
    if (*str1 > *str2)
      return 1;
  } while ((*str1++ && *str2++));
  return 0;
}

size_t my_strlen(const char *str)
{
  const char *pointer = str;
  while ((*pointer++))
    ;
  return (pointer - 1) - str;
}