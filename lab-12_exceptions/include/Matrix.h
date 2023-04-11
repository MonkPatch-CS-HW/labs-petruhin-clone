#ifndef LAB_08_MATRIX_H
#define LAB_08_MATRIX_H

#include <iostream>
#include <sstream>
#include <vector>

class MatrixError : public std::exception
{
public:
  MatrixError(std::string operation, std::string error);

  const char *what() const noexcept override;

private:
  std::string generate_text(std::string operation, std::string error);
  std::string _msg;
};

class Matrix
{
public:
  Matrix(size_t r = 0, size_t c = 0);
  Matrix(const Matrix &m);
  ~Matrix();

  size_t get_rows() const;
  size_t get_cols() const;
  void set(size_t i, size_t j, int val);
  int get(size_t i, size_t j) const;

  void load(std::string filename);
  void print(std::ostream &out) const;
  void read(std::istream &in);

  friend std::ostream &operator<<(std::ostream &out, const Matrix &matrix);
  friend std::istream &operator>>(std::istream &in, Matrix &matrix);

  Matrix operator+(const Matrix &m) const;
  Matrix operator-(const Matrix &m) const;
  Matrix operator*(const Matrix &m) const;

  Matrix &operator=(const Matrix &m);
  Matrix &operator+=(const Matrix &m);
  Matrix &operator-=(const Matrix &m);
  Matrix &operator*=(const Matrix &m);

  bool operator==(const Matrix &m) const;
  bool operator!=(const Matrix &m) const;

private:
  size_t _rows;
  size_t _cols;
  std::vector<int> _data;
};

#endif
