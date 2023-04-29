#include <cstring>
#include <iostream>

#include "HuffmanCompressor.hpp"

using namespace std;

int main() {
  HuffmanCompressor hc;
  {
    std::ifstream ifile("ifile.bin", std::ios::binary | std::ios::in);
    std::ofstream mfile("mfile.bin", std::ios::binary | std::ios::out);
    ifile.seekg(0, std::ios::end);
    std::streamsize size = ifile.tellg();
    ifile.seekg(0, std::ios::beg);

    char *buffer = new char[size];
    if (!ifile.read(buffer, size))
      throw std::logic_error(std::string("TODO"));

    hc.compress(buffer, size, mfile);
  }
  {
    std::ifstream mfile("mfile.bin", std::ios::binary | std::ios::in);
    std::ofstream ofile("ofile.bin", std::ios::binary | std::ios::out);
    mfile.seekg(0, std::ios::beg);

    char *buffer = nullptr;
    size_t n = hc.decompress(buffer, mfile);

    ofile.write(buffer, n);
  }
  return 0;
}
