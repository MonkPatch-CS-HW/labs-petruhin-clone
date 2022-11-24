#ifndef STR_H
#define STR_H

#include <stddef.h>

char *my_strcpy(char *destination, const char *source);
char *my_strcat(char *destination, const char *source);
int my_strcmp(const char *str1, const char *str2);
size_t my_strlen(const char *str);

#endif // STR_H