#include <algorithm>
#include <chrono>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <vector>

#include "HuffmanNode.hpp"
#include "HuffmanTree.hpp"

HuffmanTree::HuffmanTree(HuffmanNode *rootNode) : _rootNode(rootNode) {}

HuffmanTree::HuffmanTree(const HuffmanTree &other)
    : HuffmanTree(nodeFromTable(other.generateTable())) {}

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

bool HuffmanTree::hasChar(unsigned char ch) {
  return this->_rootNode->hasChar(ch);
}

HuffmanTree HuffmanTree::fromBuffer(const std::vector<char> &buffer) {
  std::map<unsigned char, HuffmanNode *> nodemap;
  for (size_t i = 0; i < buffer.size(); i++) {
    unsigned char ch = buffer[i];

    if (nodemap.count(ch)) {
      nodemap[ch]->incCount();
    } else {
      std::set<unsigned char> charset{static_cast<unsigned char>(ch)};
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

HuffmanTree HuffmanTree::fromTable(const std::vector<char> &table) {
  return HuffmanTree::nodeFromTable(table);
}

HuffmanNode *HuffmanTree::nodeFromTable(const std::vector<char> &table) {
  // std::chrono::time_point<std::chrono::system_clock> now =
  //     std::chrono::system_clock::now();

  HuffmanNode *rootNode = new HuffmanNode(nullptr);
  for (int i = 0; i < 256; i++) {
    rootNode->tryInsertLeftmost(i, table[i]);
  }

  // std::chrono::time_point<std::chrono::system_clock> end =
  //     std::chrono::system_clock::now();
  // std::cout << "nodeFromTable() took " << std::chrono::duration_cast<std::chrono::milliseconds>(end - now).count()
  //           << "ms of time" << std::endl;
  return rootNode;
}

int HuffmanTree::getCodeLen(unsigned char ch) const {
  int len = 0;
  for (HuffmanNode *node = _rootNode; node != nullptr;
       node = node->select(ch), len++) {

    if (node->isLeaf() && node->getChar() == ch)
      return len;
  }

  return 0;
}

std::vector<char> HuffmanTree::normalize() {
  std::vector<char> table = generateTable();

  delete _rootNode;
  _rootNode = nodeFromTable(table);

  return table;
}

HuffmanNode *HuffmanTree::getRootNode() { return _rootNode; }

void HuffmanTree::printTable() {
  std::vector<char> table = generateTable();

  std::cout << "unsigned char table[256] = { ";

  for (int i = 0; i < 256; i++)
    std::cout << table[i] << ", ";

  std::cout << "};" << std::endl;
}

std::vector<char> HuffmanTree::generateTable() const {
  // std::chrono::time_point<std::chrono::system_clock> now =
  //     std::chrono::system_clock::now();
  std::vector<char> table(256);
  for (int i = 0; i < 256; i++)
    table[i] = getCodeLen(i);
  // std::chrono::time_point<std::chrono::system_clock> end =
  //     std::chrono::system_clock::now();
  // std::cout << "generateTable() took " << std::chrono::duration_cast<std::chrono::milliseconds>(end - now).count()
  //           << "ms of time" << std::endl;
  return table;
}

bool HuffmanTree::tryInsertLeftmost(unsigned char ch, int len) {
  bool result = _rootNode->tryInsertLeftmost(ch, len);

  return result;
}
