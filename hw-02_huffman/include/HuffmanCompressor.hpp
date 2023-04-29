#ifndef HUFFMAN_COMPRESSOR_HPP
#define HUFFMAN_COMPRESSOR_HPP

#include <fstream>

class HuffmanCompressor {
public:
  void compress(char *buffer, size_t n, std::ofstream &fout);
  size_t decompress(char *&buffer, std::ifstream &fin);
};

#endif
