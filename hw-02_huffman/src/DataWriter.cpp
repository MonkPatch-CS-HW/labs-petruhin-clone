#include <fstream>
#include <iostream>

#include "DataWriter.hpp"
#include "HuffmanNode.hpp"

DataWriter::DataWriter(HuffmanTree *tree, BitWriter writer)
    : _tree(tree), _writer(writer) {}

bool DataWriter::tryWriteChar(unsigned char ch) {
  HuffmanNode *node = _tree->getRootNode();
  while (!node->isEmpty()) {
    HuffmanNode *next = node->select(ch);

    if (next == nullptr)
      return false;

    if (!_writer.tryWriteBit(next == node->getRight()))
      return false;

    node = next;

    if (node->isLeaf())
      return true;
  }
  return false;
}

void DataWriter::writeChar(unsigned char ch) {
  if (!tryWriteChar(ch))
    throw std::logic_error(std::string("TODO"));
}

void DataWriter::flush() { _writer.flush(); }
