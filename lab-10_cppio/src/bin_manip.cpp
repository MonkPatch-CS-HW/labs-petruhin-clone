#include "bin_manip.h"

std::ofstream &operator<<(std::ofstream &out, write_le_int32 wr)
{
  out.write(reinterpret_cast<const char *>(&wr._data), sizeof(int32_t));
  return out;
}

std::ifstream &operator>>(std::ifstream &in, read_le_int32 rd)
{
  in.read(reinterpret_cast<char *>(&rd._data), sizeof(int32_t));
  return in;
}

std::ofstream &operator<<(std::ofstream &out, write_bool wr)
{
  out.write(reinterpret_cast<const char *>(&wr._data), sizeof(bool));
  return out;
}

std::ifstream &operator>>(std::ifstream &in, read_bool rd)
{
  in.read(reinterpret_cast<char *>(&rd._data), sizeof(bool));
  return in;
}

std::ofstream &operator<<(std::ofstream &out, write_c_str wr)
{
  out << wr._data << '\0';
  return out;
}

std::ifstream &operator>>(std::ifstream &in, read_c_str rd)
{
  std::getline(in, rd._data, '\0');
  return in;
}
