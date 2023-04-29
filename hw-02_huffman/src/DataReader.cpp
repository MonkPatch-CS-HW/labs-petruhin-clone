#include <fstream>

#include "DataReader.hpp"
#include "HuffmanNode.hpp"

DataReader::DataReader(HuffmanTree *tree, BitReader reader) : _tree(tree), _reader(reader) {}

bool DataReader::tryReadChar(unsigned char &ch) {
  HuffmanNode *node = _tree->getRootNode();
  unsigned char bit;

  while (!node->isEmpty()) {
    if (!_reader.tryReadBit(bit))
      return false;

    node = node->getChild(bit);

    if (node->isLeaf()){
      ch = node->getChar();
      return true;
    }
  }

  return false;
}

unsigned char DataReader::readChar() {
  unsigned char ch;
  if (!tryReadChar(ch))
    throw std::logic_error(std::string("TODO"));

  return ch;
}

void DataReader::flush() {
  _reader.flush();
}
