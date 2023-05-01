#include <fstream>
#include <iostream>
#include <sstream>

#include "DataReader.hpp"
#include "HuffmanNode.hpp"
#include "exceptions.hpp"

DataReader::DataReader(HuffmanTree &tree, BitReader reader)
    : _tree(tree), _reader(reader) {}

unsigned char DataReader::readChar() {
  HuffmanNode *node = _tree.getRootNode();

  std::stringstream code;

  while (!node->isEmpty()) {
    unsigned char bit = _reader.readBit();
    code << (int)bit;

    node = node->getChild(bit);

    if (node->isLeaf())
      return node->getChar();
  }

  throw DecodingException("could not read character from compressed stream");
}

size_t DataReader::flush() { return _reader.flush(); }
