#include <fstream>
#include <iostream>
#include <sstream>

#include "DataWriter.hpp"
#include "HuffmanNode.hpp"

DataWriter::DataWriter(HuffmanTree &tree, BitWriter writer)
    : _tree(tree), _writer(writer) {}

void DataWriter::writeChar(unsigned char ch) {
  std::stringstream code;
  HuffmanNode *node = _tree.getRootNode();

  while (!node->isEmpty()) {
    HuffmanNode *next = node->select(ch);

    if (next == nullptr)
      throw std::runtime_error("could not write character to compressed stream "
                               "(incorrect tree, select=nullptr)");

    _writer.writeBit(next == node->getRight());
    code << (int)(next == node->getRight());

    node = next;

    if (node->isLeaf())
      return;
  }

  throw std::runtime_error("could not write character to compressed stream "
                           "(incorrect tree, empty node)");
}

size_t DataWriter::flush() { return _writer.flush(); }
