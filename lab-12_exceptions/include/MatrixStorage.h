#include <vector>
#include <string>

#include "Matrix.h"

class MatrixStorage
{
public:
  MatrixStorage();

  void load(int reg, std::string filename);
  void read(int reg, std::istream &in);
  void print(int reg, std::ostream &out);
  void print_elem(int reg, size_t r, size_t c, std::ostream &out);
  void add(int reg1, int reg2);
  void mul(int reg1, int reg2);

private:
  std::vector<Matrix> _matrices;
};