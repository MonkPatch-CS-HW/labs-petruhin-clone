#include <algorithm>
#include <chrono>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <vector>

#include "HuffmanNode.hpp"
#include "HuffmanTree.hpp"

HuffmanTree::HuffmanTree(HuffmanNode *rootNode)
    : _rootNode(rootNode) {
  normalize();
}

HuffmanTree::HuffmanTree(const HuffmanTree &other)
    : HuffmanTree(nodeFromTable(other.generateTable())) {}

HuffmanTree &HuffmanTree::operator=(HuffmanTree &other) {
  delete this->_rootNode;

  this->_rootNode = nodeFromTable(other.generateTable());

  return *this;
}

HuffmanTree::~HuffmanTree() { delete _rootNode; }

std::pair<HuffmanNode *, HuffmanNode *>
findToCombine(std::set<HuffmanNode *> nodeset) {
  HuffmanNode *smallest = nullptr;
  HuffmanNode *secondSmallest = nullptr;
  for (auto value : nodeset) {
    if (smallest == nullptr) {
      smallest = value;
    } else if (secondSmallest == nullptr) {
      secondSmallest = value;
    } else if (value->getCount() < secondSmallest->getCount()) {
      secondSmallest = value;
    } else {
      continue;
    }

    if (smallest != nullptr && secondSmallest != nullptr &&
        secondSmallest->getCount() < smallest->getCount())
      std::swap(smallest, secondSmallest);
  }
  return std::pair<HuffmanNode *, HuffmanNode *>(smallest, secondSmallest);
}

bool HuffmanTree::hasChar(unsigned char ch) const {
  return this->_rootNode->hasChar(ch);
}

HuffmanTree HuffmanTree::fromBuffer(const std::vector<char> &buffer) {
  std::map<unsigned char, HuffmanNode *> nodemap;
  for (size_t i = 0; i < buffer.size(); i++) {
    unsigned char ch = buffer[i];

    if (nodemap.count(ch)) {
      nodemap[ch]->incCount();
    } else {
      std::set<unsigned char> charset{ch};
      nodemap[ch] = new HuffmanNode(charset, 1);
    }
  }

  std::set<HuffmanNode *> nodeset;
  for (auto &[key, value] : nodemap)
    nodeset.insert(value);

  if (nodeset.size() == 1)
    nodeset.insert(new HuffmanNode(nullptr));

  while (nodeset.size() > 1) {
    auto [first, second] = findToCombine(nodeset);
    std::string strFirst = first->charsetString();
    std::string strSecond = second->charsetString();

    HuffmanNode *joined = first->join(second);
    nodeset.erase(first);
    nodeset.erase(second);
    nodeset.insert(joined);
  }
  HuffmanNode *rootNode = *nodeset.begin();
  return HuffmanTree(rootNode);
}

HuffmanTree HuffmanTree::fromTable(const std::vector<unsigned char> &table) {
  return HuffmanTree(HuffmanTree::nodeFromTable(table));
}

HuffmanNode *
HuffmanTree::nodeFromTable(const std::vector<unsigned char> &table) {
  HuffmanNode *rootNode = new HuffmanNode(nullptr);
  for (int i = 0; i < 256; i++)
    rootNode->tryInsertLeftmost(i, table[i]);

  return rootNode;
}

int HuffmanTree::getCodeLen(unsigned char ch) const {
  int len = 0;
  for (const HuffmanNode *node = _rootNode; node != nullptr;
       (node = node->select(ch)) && node != nullptr, len++) {

    if (node->isLeaf() && node->getChar() == ch)
      return len;
  }

  return 0;
}

void HuffmanTree::normalize() {
  _table = generateTable();

  delete _rootNode;
  _rootNode = nodeFromTable(_table);
}

const std::vector<unsigned char> &HuffmanTree::getTable() const {
  return _table;
}

const HuffmanNode *HuffmanTree::getRootNode() const {
  return _rootNode;
}

void HuffmanTree::printTable() const {
  std::vector<unsigned char> table = generateTable();

  std::cout << "unsigned char table[256] = { ";

  for (int i = 0; i < 256; i++)
    std::cout << (int)table[i] << ", ";

  std::cout << "};" << std::endl;
}

std::vector<unsigned char> HuffmanTree::generateTable() const {
  std::vector<unsigned char> table(256);
  for (int i = 0; i < 256; i++)
    table[i] = getCodeLen(i);

  return table;
}

bool HuffmanTree::tryInsertLeftmost(unsigned char ch, int len) {
  bool result = _rootNode->tryInsertLeftmost(ch, len);

  if (result)
    _consistent = false;

  return result;
}
