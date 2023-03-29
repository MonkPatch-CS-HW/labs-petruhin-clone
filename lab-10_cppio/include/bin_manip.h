#ifndef LAB10_BIN_MANIP_H_INCLUDED
#define LAB10_BIN_MANIP_H_INCLUDED

#include <stdint.h>
#include <fstream>
#include <string>

class write_le_int32
{
public:
  explicit write_le_int32(const int32_t &data) : _data(data) {}

  friend std::ofstream &operator<<(std::ofstream &out, write_le_int32 wr);

private:
  const int32_t& _data;
};

class read_le_int32
{
public:
  explicit read_le_int32(int32_t &data) : _data(data) {}

  friend std::ifstream &operator>>(std::ifstream &in, read_le_int32 rd);

private:
  int32_t &_data;
};

class write_bool
{
public:
  explicit write_bool(const bool &data) : _data(data) {}

  friend std::ofstream &operator<<(std::ofstream &out, write_bool wr);

private:
  const bool &_data;
};

class read_bool
{
public:
  explicit read_bool(bool &data) : _data(data) {}

  friend std::ifstream &operator>>(std::ifstream &in, read_bool rd);

private:
  bool &_data;
};

class write_c_str
{
public:
  explicit write_c_str(const std::string &data) : _data(data) {}

  friend std::ofstream &operator<<(std::ofstream &out, write_c_str wr);

private:
  const std::string& _data;
};

class read_c_str
{
public:
  explicit read_c_str(std::string &data) : _data(data) {}

  friend std::ifstream &operator>>(std::ifstream &in, read_c_str rd);

private:
  std::string& _data;
};

#endif
