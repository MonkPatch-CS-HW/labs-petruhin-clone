#include <algorithm>
#include <iostream>
#include <map>
#include <numeric>
#include <set>

#include "HuffmanNode.hpp"
#include "HuffmanTree.hpp"

HuffmanTree::HuffmanTree(HuffmanNode *rootNode) : _rootNode(rootNode) {}

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

HuffmanTree *HuffmanTree::fromText(std::string string) {
  std::map<unsigned char, HuffmanNode *> nodemap;
  for (auto &ch : string) {
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

  while (nodeset.size() > 1) {
    auto [first, second] = findToCombine(nodeset);
    std::string strFirst = first->charsetString();
    std::string strSecond = second->charsetString();

    // first->print();
    // second->print();
    // std::cout << "\n\n\n\n";

    HuffmanNode *joined = first->join(second);
    nodeset.erase(first);
    nodeset.erase(second);
    nodeset.insert(joined);
  }
  HuffmanNode *rootNode = *nodeset.begin();
  return new HuffmanTree(rootNode);
}

HuffmanTree *HuffmanTree::fromTable(unsigned char *data) {
  HuffmanTree *tree = new HuffmanTree();
  for (int i = 0; i < 256; i++) {
    tree->tryInsertLeftmost(i, data[i]);
  }
  return tree;
}

int HuffmanTree::getCodeLen(unsigned char ch) {
  int len = 0;
  for (HuffmanNode *node = _rootNode; node != nullptr;
       node = node->select(ch), len++) {
    if (node->isLeaf() && node->getChar() == ch)
      return len;
  }
  return 0;
}

HuffmanNode *HuffmanTree::getRootNode() {
  return _rootNode;
}

void HuffmanTree::print() { _rootNode->print(); }
void HuffmanTree::printTable() {
  std::cout << "unsigned char table[256] = { ";
  for (int i = 0; i < 256; i++)
    std::cout << getCodeLen(i) << ", ";
  std::cout << "};" << std::endl;
}
bool HuffmanTree::tryInsertLeftmost(unsigned char ch, int len) {
  return _rootNode->tryInsertLeftmost(ch, len);
}
