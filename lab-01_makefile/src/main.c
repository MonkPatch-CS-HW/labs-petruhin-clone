#include "io.h"
#include "util.h"
#include "algorithm.h"

int doComputation(int, int);

// int main() {}
// int run() // instead of int main()
int main()
{
  int a = doComputation(5, 7.0);
  int b = 5;
  max(a, b);
  logDebug('!');
  return 0;
}

// int a = 5;
// int a = 6;