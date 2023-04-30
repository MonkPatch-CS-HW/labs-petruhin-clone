#ifndef DATA_READER_HPP
#define DATA_READER_HPP

#include "BitReader.hpp"
#include "HuffmanTree.hpp"

class DataReader {
private:
  HuffmanTree &_tree;
  BitReader _reader;

public:
  DataReader(HuffmanTree &tree, BitReader reader);

  unsigned char readChar();

  size_t flush();
};

#endif
