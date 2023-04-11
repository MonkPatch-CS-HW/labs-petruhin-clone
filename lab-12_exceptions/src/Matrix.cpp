#include <fstream>
#include "Matrix.h"

MatrixError::MatrixError(std::string operation, std::string error) : _msg(generate_text(operation, error))
{
}

const char *MatrixError::what() const noexcept
{
  return _msg.c_str();
}

std::string MatrixError::generate_text(std::string operation, std::string error)
{
  std::stringstream ss;
  ss << operation << ": " << error << ".";
  return ss.str();
}

Matrix::Matrix(size_t rows, size_t cols)
{
  _rows = rows;
  _cols = cols;

  _data = std::vector<int>(rows * cols);
}

Matrix::Matrix(const Matrix &m)
{
  *this = m;
}

Matrix::~Matrix()
{
}

size_t Matrix::get_rows() const
{
  return _rows;
}

size_t Matrix::get_cols() const
{
  return _cols;
}

void Matrix::set(size_t r, size_t c, int val)
{
  if (r < 0 || r >= _rows || c < 0 || c >= _cols)
    throw MatrixError("ACCESS", "bad index");

  _data[r * _cols + c] = val;
}

int Matrix::get(size_t r, size_t c) const
{
  if (r < 0 || r >= _rows || c < 0 || c >= _cols)
    throw MatrixError("ACCESS", "bad index");

  return _data[r * _cols + c];
}

void Matrix::load(std::string filename)
{
  std::ifstream fin(filename);

  if (!fin.good())
    throw MatrixError("LOAD", "unable to open file");

  try
  {
    fin >> *this;
  }
  catch (MatrixError &ex)
  {
    throw MatrixError("LOAD", "invalid file format");
  }
}

void Matrix::print(std::ostream &out) const
{
  for (size_t r = 0; r < _rows; r++)
  {
    for (size_t c = 0; c < _cols; c++)
    {
      out << get(r, c);
      if (c != _cols - 1)
        out << ' ';
    }
    out << std::endl;
  }
}

std::ostream &operator<<(std::ostream &out, const Matrix &matrix)
{
  matrix.print(out);
  return out;
}

std::istream &operator>>(std::istream &in, Matrix &matrix)
{
  matrix.read(in);
  return in;
}

void Matrix::read(std::istream &in)
{
  size_t rows, cols;
  int val;
  if (!(in >> rows >> cols))
    throw MatrixError("READ", "invalid format");

  Matrix tmp(rows, cols);
  for (size_t r = 0; r < _rows; r++)
    for (size_t c = 0; c < _cols; c++)
    {
      if (!(in >> val))
        throw MatrixError("READ", "invalid format");

      set(r, c, val);
    }

  *this = tmp;
}

Matrix &Matrix::operator=(const Matrix &m)
{
  _rows = m.get_rows();
  _cols = m.get_cols();
  _data = std::vector<int>(m._data);

  return *this;
}

Matrix Matrix::operator+(const Matrix &m) const
{
  if (m._rows != _rows || m._cols != _cols)
    throw MatrixError("ADD", "dimensions do not match");

  Matrix result(_rows, _cols);
  for (size_t r = 0; r < _rows; r++)
    for (size_t c = 0; c < _cols; c++)
      result.set(r, c, get(r, c) + m.get(r, c));

  return result;
}

Matrix Matrix::operator-(const Matrix &m) const
{
  Matrix result(_rows, _cols);
  for (size_t r = 0; r < _rows; r++)
    for (size_t c = 0; c < _cols; c++)
      result.set(r, c, get(r, c) - m.get(r, c));

  return result;
}

Matrix Matrix::operator*(const Matrix &m) const
{
  if (_cols != m._rows)
    throw MatrixError("MUL", "#arg1.columns != #arg2.rows");

  Matrix result(_rows, m.get_cols());
  for (size_t r = 0; r < _rows; r++)
  {
    for (size_t c = 0; c < m.get_cols(); c++)
    {
      int sum = 0;
      for (size_t k = 0; k < _cols; k++)
        sum += get(r, k) * m.get(k, c);

      result.set(r, c, sum);
    }
  }
  return result;
}

Matrix &Matrix::operator+=(const Matrix &m)
{
  return *this = *this + m;
}

Matrix &Matrix::operator-=(const Matrix &m)
{
  return *this = *this - m;
}

Matrix &Matrix::operator*=(const Matrix &m)
{
  return *this = *this * m;
}

bool Matrix::operator==(const Matrix &m) const
{
  if (_rows != m.get_rows() || _cols != m.get_cols())
    return false;

  for (size_t r = 0; r < _rows; r++)
    for (size_t c = 0; c < _cols; c++)
      if (get(r, c) != m.get(r, c))
        return false;

  return true;
}

bool Matrix::operator!=(const Matrix &m) const
{
  return !(*this == m);
}
