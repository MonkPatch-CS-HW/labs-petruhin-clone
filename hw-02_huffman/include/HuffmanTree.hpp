#ifndef HUFFMAN_TREE_HPP
#define HUFFMAN_TREE_HPP

#include <string>
#include <vector>

#include "HuffmanNode.hpp"

class HuffmanTree {
private:
  HuffmanNode *_rootNode;

public:
  static HuffmanTree *fromText(char *buffer, size_t n);
  static HuffmanTree *fromTable(unsigned char *buffer);

  HuffmanTree(HuffmanNode *rootNode = new HuffmanNode(nullptr));
  ~HuffmanTree();

  HuffmanNode *getRootNode();

  int getCodeLen(unsigned char ch);

  unsigned char* generateTable();

  void print();
  void printTable();
  bool tryInsertLeftmost(unsigned char ch, int len);
};

#endif
