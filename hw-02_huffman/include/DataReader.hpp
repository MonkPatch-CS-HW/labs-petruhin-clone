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

  bool tryReadChar(unsigned char &ch);
  unsigned char readChar();

  void flush();
};

#endif
