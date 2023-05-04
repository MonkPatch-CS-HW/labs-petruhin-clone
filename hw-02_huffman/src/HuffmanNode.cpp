#include <algorithm>
#include <exception>
#include <fstream>
#include <iostream>
#include <numeric>
#include <sstream>

#include "HuffmanNode.hpp"
#include "exceptions.hpp"

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
  if (!isRoot() || !other->isRoot())
    throw HuffmanNodeException("cannot join nodes which are not both root nodes");

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

bool HuffmanNode::tryInsertLeftmost(unsigned char ch, int len) {
  if (len < 0 || (len == 0 && isRoot()))
    return false;

  if (len == 0) {
    if (isEmpty()) {
      setChar(ch);
      return true;
    }
    return false;
  }

  if (isLeaf())
    return false;

  if (_left == nullptr)
    _left = new HuffmanNode(this);

  if (_left->tryInsertLeftmost(ch, len - 1))
    return true;

  if (_right == nullptr)
    _right = new HuffmanNode(this);

  if (_right->tryInsertLeftmost(ch, len - 1))
    return true;

  return false;
}

int HuffmanNode::getCount() const { return _count; }
void HuffmanNode::setCount(int count) { _count = count; }
void HuffmanNode::incCount() { _count += 1; }

std::set<unsigned char> HuffmanNode::getCharset() const { return _charset; }

bool HuffmanNode::hasChar(unsigned char ch) const {
  return _charset.count(ch) > 0;
}

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
  if (!isEmpty())
    throw HuffmanNodeException(
        "trying to init char when the node is already not empty");

  _charset = std::set<unsigned char>();
  addChar(ch);
}

unsigned char HuffmanNode::getChar() const {
  if (!isLeaf())
    throw HuffmanNodeException(
        "trying to get char of the node which is not a leaf");

  return *this->_charset.begin();
}

void HuffmanNode::setChar(unsigned char ch) {
  if (isEmpty())
    return initChar(ch);

  if (!isLeaf())
    throw HuffmanNodeException(
        "trying to set char of the node which is not a leaf");

  unsigned char oldCh = getChar();
  changeChar(oldCh, ch);
}

const HuffmanNode *HuffmanNode::getParent() const { return _parent; }

const HuffmanNode *HuffmanNode::getLeft() const { return _left; }

const HuffmanNode *HuffmanNode::getRight() const { return _right; }

const HuffmanNode *HuffmanNode::getChild(bool right) const {
  return right ? getRight() : getLeft();
}

const HuffmanNode *HuffmanNode::select(unsigned char ch) const {
  if (_left != nullptr && _left->hasChar(ch))
    return _left;

  if (_right != nullptr && _right->hasChar(ch))
    return _right;

  return nullptr;
}

bool HuffmanNode::isEmpty() const { return _charset.size() == 0; }
bool HuffmanNode::isLeaf() const {
  return _charset.size() == 1 && _left == nullptr && _right == nullptr;
}
bool HuffmanNode::isRoot() const { return _parent == nullptr; }
