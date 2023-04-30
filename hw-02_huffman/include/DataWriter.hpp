#ifndef DATA_WRITER_HPP
#define DATA_WRITER_HPP

#include "BitWriter.hpp"
#include "HuffmanTree.hpp"

class DataWriter {
private:
  HuffmanTree &_tree;
  BitWriter _writer;
  size_t _bytesWritten;

public:
  DataWriter(HuffmanTree &tree, BitWriter writer);

  bool tryWriteChar(unsigned char ch);
  void writeChar(unsigned char ch);

  size_t flush();
};

#endif
