#ifndef HUFFMAN_TREE_HPP
#define HUFFMAN_TREE_HPP

#include <string>
#include <vector>

#include "HuffmanNode.hpp"

class HuffmanTree {
private:
  HuffmanNode *_rootNode;
  std::vector<char> _cachedTable;

  bool tryInsertLeftmost(unsigned char ch, int len);
  static HuffmanNode *nodeFromTable(const std::vector<unsigned char> &table);

public:
  static HuffmanTree fromBuffer(const std::vector<char> &buffer);
  static HuffmanTree fromTable(const std::vector<unsigned char> &table);

  HuffmanTree(HuffmanNode *rootNode = new HuffmanNode(nullptr));

  HuffmanTree(const HuffmanTree &other);
  HuffmanTree &operator=(HuffmanTree &other) = delete;

  ~HuffmanTree();

  bool hasChar(unsigned char ch);

  HuffmanNode *getRootNode();

  int getCodeLen(unsigned char ch) const;

  std::vector<unsigned char> generateTable() const;
  std::vector<unsigned char> normalize();

  void printTable();
};

#endif
