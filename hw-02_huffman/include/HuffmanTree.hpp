#ifndef HUFFMAN_TREE_HPP
#define HUFFMAN_TREE_HPP

#include <string>
#include <vector>

#include "HuffmanNode.hpp"

class HuffmanTree {
private:
  HuffmanNode *_rootNode;

public:
  static HuffmanTree *fromText(std::string string);
  static HuffmanTree *fromTable(unsigned char *data);

  HuffmanTree(HuffmanNode *rootNode = new HuffmanNode(nullptr));
  ~HuffmanTree();

  HuffmanNode *getRootNode();

  int getCodeLen(unsigned char ch);

  void print();
  void printTable();
  bool tryInsertLeftmost(unsigned char ch, int len);
};

#endif
