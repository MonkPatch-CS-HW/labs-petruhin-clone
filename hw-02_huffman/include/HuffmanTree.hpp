#ifndef HUFFMAN_TREE_HPP
#define HUFFMAN_TREE_HPP

#include <string>
#include <vector>

#include "HuffmanNode.hpp"

class HuffmanTree {
private:
  HuffmanNode *_rootNode;
  bool _consistent;
  std::vector<unsigned char> _table;

  bool tryInsertLeftmost(unsigned char ch, int len);
  static HuffmanNode *nodeFromTable(const std::vector<unsigned char> &table);

  HuffmanTree(HuffmanNode *rootNode = new HuffmanNode(nullptr));
  std::vector<unsigned char> normalize();
  std::vector<unsigned char> generateTable() const;

public:
  static HuffmanTree fromBuffer(const std::vector<char> &buffer);
  static HuffmanTree fromTable(const std::vector<unsigned char> &table);

  HuffmanTree(const HuffmanTree &other);
  HuffmanTree &operator=(HuffmanTree &other);

  ~HuffmanTree();

  bool hasChar(unsigned char ch) const;

  const HuffmanNode *getRootNode();

  int getCodeLen(unsigned char ch) const;

  const std::vector<unsigned char> &getTable();

  void printTable() const;
};

#endif
