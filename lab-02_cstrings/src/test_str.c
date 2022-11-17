#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "str.h"

void test_my_strcpy()
{
  char str1[10];
  char str2[10] = "1234a6789";
  
  char str01[10];
  char str02[10] = "";

  char *str10 = my_strcpy(str1, str2);
  assert(str10 == str1);
  assert(my_strcmp(str10, str2) == 0);

  char *str010 = my_strcpy(str01, str02);
  assert(str010 == str01);
  assert(my_strlen(str01) == 0);
}

void test_my_strcat()
{
  char str1[10] = "1234";
  char str2[10] = "a6789";
  char str3[10] = "1234a6789";
  char *str01 = my_strcat(str1, str2);
  assert(str01 == str1);
  assert(my_strcmp(str01, str3) == 0);
}

void test_my_strlen()
{
  char str0[10] = "";
  char str9[10] = "123456789";
  assert(my_strlen(str0) == 0);
  assert(my_strlen(str9) == 9);
}

void test_my_strcmp()
{
  char str01[10] = "";
  char str02[10] = "";
  char str11[10] = "1";
  char str12[10] = "1";
  char str13[10] = "a";
  char str21[10] = "1a";
  char str22[10] = "1a";
  char str23[10] = "11";

  assert(my_strcmp(str01, str01) == 0);
  assert(my_strcmp(str01, str02) == 0);
  assert(my_strcmp(str11, str12) == 0);
  assert(my_strcmp(str21, str22) == 0);

  assert(my_strcmp(str01, str11) < 0);
  assert(my_strcmp(str12, str13) < 0);
  assert(my_strcmp(str22, str13) < 0);
  assert(my_strcmp(str12, str21) < 0);
  assert(my_strcmp(str12, str23) < 0);

  assert(my_strcmp(str11, str01) > 0);
  assert(my_strcmp(str13, str12) > 0);
  assert(my_strcmp(str13, str22) > 0);
  assert(my_strcmp(str21, str12) > 0);
  assert(my_strcmp(str23, str12) > 0);
}