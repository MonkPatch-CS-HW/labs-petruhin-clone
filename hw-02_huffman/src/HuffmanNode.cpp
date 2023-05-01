#include <algorithm>
#include <exception>
#include <fstream>
#include <iostream>
#include <numeric>
#include <sstream>

#include "exceptions.hpp"
#include "HuffmanNode.hpp"

HuffmanNode::HuffmanNode(std::set<unsigned char> charset, int count,
                         HuffmanNode *parent)
    : _left(nullptr), _right(nullptr), _parent(nullptr),
      _charset(std::move(charset)), _count(count) {}

HuffmanNode::HuffmanNode(unsigned char ch, int count, HuffmanNode *parent)
    : _left(nullptr), _right(nullptr), _parent(nullptr),
      _charset(std::set<unsigned char>{ch}), _count(count) {}

HuffmanNode::HuffmanNode(HuffmanNode *parent)
    : _left(nullptr), _right(nullptr), _parent(parent),
      _charset(std::set<unsigned char>()), _count(0) {}

HuffmanNode::HuffmanNode(HuffmanNode *left, HuffmanNode *right,
                         HuffmanNode *parent, std::set<unsigned char> charset,
                         int count)
    : _left(left), _right(right), _parent(parent), _charset(std::move(charset)),
      _count(count) {}

HuffmanNode::~HuffmanNode() {
  delete _left;
  delete _right;
}

HuffmanNode *HuffmanNode::join(HuffmanNode *other) {
  std::set<unsigned char> newset;
  std::merge(_charset.begin(), _charset.end(), other->_charset.begin(),
             other->_charset.end(), std::inserter(newset, newset.begin()));
  HuffmanNode *newNode =
      new HuffmanNode(this, other, _parent, newset, _count + other->_count);
  _parent = newNode;
  other->_parent = newNode;
  return newNode;
}

std::string HuffmanNode::charsetString() const {
  std::stringstream ss;
  for (auto ch : _charset)
    ss << '<' << (int)ch << '>';

  return ss.str();
}

void HuffmanNode::print(std::string prefix, bool isLeft) const {
  print(std::cout, prefix, isLeft);
}

void HuffmanNode::print(std::ostream &out, std::string prefix,
                        bool isLeft) const {
  out << prefix;
  out << (isLeft ? "├──" : "└──");
  std::string str = charsetString();
  out << str << " (" << _count << ")" << std::endl;

  if (_left != nullptr)
    _left->print(out, prefix + (isLeft ? "│   " : "    "), true);
  if (_right != nullptr)
    _right->print(out, prefix + (isLeft ? "│   " : "    "), false);
}

void HuffmanNode::print(std::ofstream &out, std::string prefix,
                        bool isLeft) const {
  out << prefix;
  out << (isLeft ? "├──" : "└──");
  std::string str = charsetString();
  out << str << " (" << _count << ")" << std::endl;

  if (_left != nullptr)
    _left->print(out, prefix + (isLeft ? "│   " : "    "), true);
  if (_right != nullptr)
    _right->print(out, prefix + (isLeft ? "│   " : "    "), false);
}

HuffmanNode *HuffmanNode::getChild(bool right) {
  return right ? getRight() : getLeft();
}

HuffmanNode *HuffmanNode::select(unsigned char ch) {
  HuffmanNode *left = getLeft();
  HuffmanNode *right = getRight();

  if (left->hasChar(ch))
    return left;

  if (right->hasChar(ch))
    return right;

  return nullptr;
}

bool HuffmanNode::tryInsertLeftmost(unsigned char ch, int len) {
  if (len < 0 || (len == 0 && isRoot()))
    return false;

  HuffmanNode *left = getLeft();
  HuffmanNode *right = getRight();

  if (len == 0) {
    if (isEmpty()) {
      setChar(ch);
      return true;
    }
    return false;
  }

  if (isLeaf())
    return false;

  if (left->tryInsertLeftmost(ch, len - 1))
    return true;

  if (right->tryInsertLeftmost(ch, len - 1))
    return true;

  return false;
}

int HuffmanNode::getCount() { return _count; }
void HuffmanNode::setCount(int count) { _count = count; }
void HuffmanNode::incCount() { _count += 1; }

std::set<unsigned char> HuffmanNode::getCharset() { return _charset; }

bool HuffmanNode::hasChar(unsigned char ch) { return _charset.count(ch) > 0; }

void HuffmanNode::changeChar(unsigned char oldCh, unsigned char newCh) {
  removeChar(oldCh);
  addChar(newCh);
}

void HuffmanNode::addChar(unsigned char ch) {
  _charset.insert(ch);

  if (!isRoot())
    _parent->addChar(ch);
}

void HuffmanNode::removeChar(unsigned char ch) {
  _charset.erase(ch);

  if (!isRoot())
    _parent->removeChar(ch);
}

void HuffmanNode::initChar(unsigned char ch) {
  if (!this->isEmpty())
    throw HuffmanNodeException(
        "trying to init char when the node is already not empty");

  _charset = std::set<unsigned char>();
  addChar(ch);
}

unsigned char HuffmanNode::getChar() {
  if (!this->isLeaf())
    throw HuffmanNodeException(
        "trying to get char of the node which is not a leaf");

  return *this->_charset.begin();
}

void HuffmanNode::setChar(unsigned char ch) {
  if (this->isEmpty())
    return initChar(ch);

  if (!this->isLeaf())
    throw HuffmanNodeException(
        "trying to set char of the node which is not a leaf");

  unsigned char oldCh = getChar();
  changeChar(oldCh, ch);
}

HuffmanNode *HuffmanNode::getParent() { return _parent; }

HuffmanNode *HuffmanNode::getLeft() {
  if (_left == nullptr)
    _left = new HuffmanNode(this);

  return _left;
}

HuffmanNode *HuffmanNode::getRight() {
  if (_right == nullptr)
    _right = new HuffmanNode(this);

  return _right;
}

bool HuffmanNode::isEmpty() { return _charset.size() == 0; }
bool HuffmanNode::isLeaf() {
  HuffmanNode *left = getLeft();
  HuffmanNode *right = getRight();
  return _charset.size() == 1 && left->isEmpty() && right->isEmpty();
}
bool HuffmanNode::isRoot() { return _parent == nullptr; }
