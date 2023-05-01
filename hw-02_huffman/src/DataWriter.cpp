#include <fstream>
#include <iostream>
#include <sstream>

#include "DataWriter.hpp"
#include "HuffmanNode.hpp"

DataWriter::DataWriter(HuffmanTree &tree, BitWriter writer)
    : _tree(tree), _writer(writer) {
  initHuffmanCodes();
}

const std::vector<unsigned char> &DataWriter::getHuffmanCode(unsigned char ch) {
  if (_huffmanCodes[ch].size() == 0)
    throw std::runtime_error("could not find huffman code for a character");

  return _huffmanCodes[ch];
}

std::vector<unsigned char> DataWriter::findHuffmanCode(unsigned char ch) {
  std::vector<unsigned char> code;
  HuffmanNode *node = _tree.getRootNode();

  while (!node->isEmpty()) {
    HuffmanNode *next = node->select(ch);

    if (next == nullptr)
      throw std::runtime_error("could not get next bit for a symbol "
                               "(incorrect tree, select=nullptr)");

    code.push_back(next == node->getRight());

    node = next;

    if (node->isLeaf())
      return code;
  }

  throw std::runtime_error("could not get next bit for a symbol "
                           "(incorrect tree, empty node)");
}

void DataWriter::initHuffmanCodes() {
  for (int i = 0; i < 256; i++) {
    if (!_tree.hasChar(i))
      continue;

    _huffmanCodes[i] = findHuffmanCode(i);
  }
}

void DataWriter::writeChar(unsigned char ch) {
  const std::vector<unsigned char> &code = getHuffmanCode(ch);

  for (unsigned char ch : code)
    _writer.writeBit(ch);
}

size_t DataWriter::flush() { return _writer.flush(); }
