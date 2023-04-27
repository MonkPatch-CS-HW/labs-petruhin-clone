#ifndef HUFFMAN_NODE_HPP
#define HUFFMAN_NODE_HPP

#include <bitset>
#include <set>
#include <string>

class HuffmanNode {
private:
  HuffmanNode *_left;
  HuffmanNode *_right;
  HuffmanNode *_parent;
  std::set<char> _charset;
  int _count;

  bool hasChar(char ch);
  void addChar(char ch);
  void changeChar(char oldCh, char newCh);
  void removeChar(char ch);

public:
  HuffmanNode(std::set<char> charset = std::set<char>(), int count = 0,
              HuffmanNode *parent = nullptr);
  HuffmanNode(char ch = '\0', int count = 0, HuffmanNode *parent = nullptr);
  HuffmanNode(HuffmanNode *parent);
  HuffmanNode(HuffmanNode *left, HuffmanNode *right, HuffmanNode *parent,
              std::set<char> charset, int count);
  ~HuffmanNode();

  HuffmanNode *join(HuffmanNode *other);

  std::string charsetString();
  void print(std::string prefix = "", bool isLeft = false) const;
  bool tryInsertLeftmost(char ch, int len);

  HuffmanNode *getLeft();
  HuffmanNode *getRight();
  HuffmanNode *getParent();
  HuffmanNode *select(char ch);

  std::set<char> getCharset();

  char getChar();
  void setChar(char ch);
  void initChar(char ch);
  void clearChar();

  int getCount();
  void setCount(int count);
  void incCount();

  bool isEmpty();
  bool isLeaf();
  bool isRoot();
};

#endif
