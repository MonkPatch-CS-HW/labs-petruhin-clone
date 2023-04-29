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
    size_t size = ifile.tellg();
    ifile.seekg(0, std::ios::beg);

    std::vector<char> buffer(size);
    if (!ifile.read(buffer.data(), size))
      throw std::logic_error(std::string("TODO"));

    hc.compress(buffer, mfile);
  }
  {
    std::ifstream mfile("mfile.bin", std::ios::binary | std::ios::in);
    std::ofstream ofile("ofile.bin", std::ios::binary | std::ios::out);
    mfile.seekg(0, std::ios::beg);

    std::vector<char> buffer;
    hc.decompress(mfile, buffer);

    ofile.write(buffer.data(), buffer.size());
  }
  return 0;
}
