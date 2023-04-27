#ifndef HUFFMAN_TREE_HPP
#define HUFFMAN_TREE_HPP

#include "HuffmanNode.hpp"
#include <string>
class HuffmanTree {
private:
  HuffmanNode *_rootNode;

public:
  static HuffmanTree *fromText(std::string string);
  static HuffmanTree *fromTable(char *data);

  HuffmanTree(HuffmanNode *rootNode = new HuffmanNode(nullptr));
  ~HuffmanTree();

  int getCodeLen(char ch);
  void print();
  void printTable();
  bool tryInsertLeftmost(char ch, int len);
};

#endif
