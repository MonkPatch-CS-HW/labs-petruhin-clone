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
  std::set<unsigned char> _charset;
  int _count;

  void addChar(unsigned char ch);
  void changeChar(unsigned char oldCh, unsigned char newCh);
  void removeChar(unsigned char ch);

public:
  HuffmanNode(std::set<unsigned char> charset = std::set<unsigned char>(),
              int count = 0, HuffmanNode *parent = nullptr);
  HuffmanNode(unsigned char ch = '\0', int count = 0,
              HuffmanNode *parent = nullptr);
  HuffmanNode(HuffmanNode *parent);
  HuffmanNode(HuffmanNode *left, HuffmanNode *right, HuffmanNode *parent,
              std::set<unsigned char> charset, int count);
  ~HuffmanNode();

  HuffmanNode *join(HuffmanNode *other);

  std::string charsetString() const;
  void print(std::string prefix = "", bool isLeft = false) const;
  void print(std::ostream &out, std::string prefix = "",
             bool isLeft = false) const;
  void print(std::ofstream &out, std::string prefix = "",
             bool isLeft = false) const;
  bool tryInsertLeftmost(unsigned char ch, int len);

  HuffmanNode *getLeft();
  HuffmanNode *getRight();
  HuffmanNode *getParent();
  HuffmanNode *getChild(bool right);
  HuffmanNode *select(unsigned char ch);

  std::set<unsigned char> getCharset();

  bool hasChar(unsigned char ch);

  unsigned char getChar();
  void setChar(unsigned char ch);
  void initChar(unsigned char ch);
  void clearChar();

  int getCount();
  void setCount(int count);
  void incCount();

  bool isEmpty();
  bool isLeaf();
  bool isRoot();
};

#endif
