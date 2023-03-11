#include <string.h>
#include "matrix.h"

Matrix::Matrix(size_t r, size_t c)
{
  make_table(r, c, false);
}

void Matrix::make_table(size_t r, size_t c, bool erase)
{
  if (erase)
  {
    for (size_t i = 0; i < _rows; i++)
    {
      delete[] _data[i];
    }
    delete[] _data;
  }

  _rows = r;
  _cols = c;

  if (_rows == 0 || _cols == 0)
    return;

  _data = new int *[_rows];
  for (size_t i = 0; i < _rows; i++)
  {
    _data[i] = new int[_cols]{};
  }
}

Matrix::Matrix(const Matrix &m)
{
  _rows = m.get_rows();
  _cols = m.get_cols();
  _data = new int *[_rows];
  for (size_t i = 0; i < _rows; i++)
  {
    _data[i] = new int[_cols];
    memcpy(_data[i], m._data[i], _cols * sizeof(int));
  }
}

Matrix::~Matrix()
{
  make_table(0, 0);
}

size_t Matrix::get_rows() const
{
  return _rows;
}

size_t Matrix::get_cols() const
{
  return _cols;
}

void Matrix::set(size_t i, size_t j, int val)
{
  _data[i][j] = val;
}

int Matrix::get(size_t i, size_t j) const
{
  return _data[i][j];
}

void Matrix::print(FILE *f)
{
  for (size_t i = 0; i < _rows; i++)
  {
    for (size_t j = 0; j < _cols; j++)
    {
      fprintf(f, "%d", _data[i][j]);
      if (j != _cols - 1)
        fprintf(f, " ");
    }
    fprintf(f, "\n");
  }
}

Matrix &Matrix::operator=(const Matrix &m)
{
  make_table(m.get_rows(), m.get_cols());

  for (size_t i = 0; i < _rows; i++)
  {
    _data[i] = new int[_cols];
    memcpy(_data[i], m._data[i], _cols * sizeof(int));
  }

  return *this;
}

Matrix Matrix::operator+(const Matrix &m) const
{
  Matrix result(_rows, _cols);
  for (size_t i = 0; i < _rows; i++)
  {
    for (size_t j = 0; j < _cols; j++)
    {
      result.set(i, j, _data[i][j] + m.get(i, j));
    }
  }
  return result;
}

Matrix Matrix::operator-(const Matrix &m) const
{
  Matrix result(_rows, _cols);
  for (size_t i = 0; i < _rows; i++)
  {
    for (size_t j = 0; j < _cols; j++)
    {
      result.set(i, j, _data[i][j] - m.get(i, j));
    }
  }
  return result;
}

Matrix Matrix::operator*(const Matrix &m) const
{
  Matrix result(_rows, m.get_cols());
  for (size_t i = 0; i < _rows; i++)
  {
    for (size_t j = 0; j < m.get_cols(); j++)
    {
      int sum = 0;
      for (size_t k = 0; k < _cols; k++)
      {
        sum += _data[i][k] * m.get(k, j);
      }
      result.set(i, j, sum);
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
  {
    return false;
  }
  for (size_t i = 0; i < _rows; i++)
  {
    for (size_t j = 0; j < _cols; j++)
    {
      if (_data[i][j] != m.get(i, j))
      {
        return false;
      }
    }
  }
  return true;
}

bool Matrix::operator!=(const Matrix &m) const
{
  return !(*this == m);
}
