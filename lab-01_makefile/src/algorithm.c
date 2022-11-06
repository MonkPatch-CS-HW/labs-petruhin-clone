#include "util.h"
#include "io.h"

int doComputation(int a, float b)
{
  int c = max(3 + a, 4 + b);
  logDebug('d');
  return c;
}
