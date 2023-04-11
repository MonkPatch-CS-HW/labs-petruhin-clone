#include "MatrixStorage.h"
#include "Matrix.h"

#include <fstream>

MatrixStorage::MatrixStorage() : _matrices(10)
{
}

void MatrixStorage::load(int reg, std::string filename)
{
  _matrices[reg].load(filename);
}

void MatrixStorage::add(int reg1, int reg2)
{
  _matrices[reg1] += _matrices[reg2];
}

void MatrixStorage::mul(int reg1, int reg2)
{
  _matrices[reg1] *= _matrices[reg2];
}

void MatrixStorage::read(int reg, std::istream& in)
{
  in >> _matrices[reg];
}

void MatrixStorage::print(int reg, std::ostream &out)
{
  out << _matrices[reg];
}

void MatrixStorage::print_elem(int reg, size_t r, size_t c, std::ostream &out)
{
  out << _matrices[reg].get(r, c) << std::endl;
}