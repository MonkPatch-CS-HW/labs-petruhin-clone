#ifndef DATA_WRITER_HPP
#define DATA_WRITER_HPP

#include <map>
#include <vector>

#include "BitWriter.hpp"
#include "HuffmanTree.hpp"

class DataWriter {
private:
  HuffmanTree &_tree;
  BitWriter _writer;
  size_t _bytesWritten;
  std::map<unsigned char, std::vector<unsigned char>> _huffmanCodes;

  std::vector<unsigned char> findHuffmanCode(unsigned char ch);
  std::vector<unsigned char> getHuffmanCode(unsigned char ch);
  void initHuffmanCodes();

public:
  DataWriter(HuffmanTree &tree, BitWriter writer);

  void writeChar(unsigned char ch);

  size_t flush();
};

#endif
