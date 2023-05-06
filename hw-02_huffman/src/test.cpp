#include <assert.h>
#include <ctime>
#include <random>
#include <sstream>
#include <streambuf>
#include <vector>

#include "BitReader.hpp"
#include "BitWriter.hpp"
#include "DataReader.hpp"
#include "DataWriter.hpp"
#include "HuffmanCompressor.hpp"
#include "HuffmanTree.hpp"

std::vector<unsigned char> getAlphabeticTable() {
  std::vector<unsigned char> table(256);
  table['a'] = 1;
  table['b'] = 2;
  table['c'] = 3;
  table['d'] = 4;
  table['e'] = 5;
  table['f'] = 6;
  table['g'] = 7;
  table['h'] = 8;
  return table;
}

HuffmanTree getAlphabeticTree() {
  return HuffmanTree::fromTable(getAlphabeticTable());
}

void testAlphabeticTreeCodeLen() {
  HuffmanTree tree = getAlphabeticTree();

  assert(tree.getCodeLen('a') == 1);
  assert(tree.getCodeLen('b') == 2);
  assert(tree.getCodeLen('c') == 3);
  assert(tree.getCodeLen('d') == 4);
  assert(tree.getCodeLen('e') == 5);
  assert(tree.getCodeLen('f') == 6);
  assert(tree.getCodeLen('g') == 7);
  assert(tree.getCodeLen('h') == 8);
}

void testBitReader() {
  std::stringstream ss;
  ss << (char)0b10101010 << (char)0b01010101;
  BitReader br(ss);

  assert(br.readBit() == 1);
  assert(br.readBit() == 0);
  assert(br.readBit() == 1);
  assert(br.readBit() == 0);
  assert(br.flush() == 1);

  assert(br.readBit() == 0);
  assert(br.readBit() == 1);
  assert(br.readBit() == 0);
  assert(br.readBit() == 1);
  assert(br.flush() == 1);
}

void testBitWriter() {
  std::stringstream ss;
  BitWriter bw(ss);

  bw.writeBit(0);
  bw.writeBit(1);
  bw.writeBit(0);
  bw.writeBit(1);
  assert(bw.flush() == 1);

  bw.writeBit(1);
  bw.writeBit(0);
  bw.writeBit(1);
  bw.writeBit(0);
  assert(bw.flush() == 1);

  std::string str = ss.str();
  assert(str[0] == (char)0b01010000);
  assert(str[1] == (char)0b10100000);
  assert(str.size() == 2);
}

void testDataWriter() {
  std::stringstream ss;
  HuffmanTree tree = getAlphabeticTree();
  BitWriter bw(ss);
  DataWriter dw(tree, bw);  

  dw.writeChar('a');
  dw.writeChar('b');
  dw.writeChar('c');
  dw.writeChar('d');
  dw.writeChar('e');
  dw.writeChar('f');
  dw.writeChar('g');
  dw.writeChar('h');
  assert(dw.flush() == 5);

  BitReader br(ss);

  // a
  assert(br.readBit() == 0);

  // b
  assert(br.readBit() == 1);
  assert(br.readBit() == 0);

  // c
  assert(br.readBit() == 1);
  assert(br.readBit() == 1);
  assert(br.readBit() == 0);

  // d
  assert(br.readBit() == 1);
  assert(br.readBit() == 1);
  assert(br.readBit() == 1);
  assert(br.readBit() == 0);

  // e
  assert(br.readBit() == 1);
  assert(br.readBit() == 1);
  assert(br.readBit() == 1);
  assert(br.readBit() == 1);
  assert(br.readBit() == 0);

  // f
  assert(br.readBit() == 1);
  assert(br.readBit() == 1);
  assert(br.readBit() == 1);
  assert(br.readBit() == 1);
  assert(br.readBit() == 1);
  assert(br.readBit() == 0);

  // g
  assert(br.readBit() == 1);
  assert(br.readBit() == 1);
  assert(br.readBit() == 1);
  assert(br.readBit() == 1);
  assert(br.readBit() == 1);
  assert(br.readBit() == 1);
  assert(br.readBit() == 0);

  // h
  assert(br.readBit() == 1);
  assert(br.readBit() == 1);
  assert(br.readBit() == 1);
  assert(br.readBit() == 1);
  assert(br.readBit() == 1);
  assert(br.readBit() == 1);
  assert(br.readBit() == 1);
  assert(br.readBit() == 0);
}

void testDataReader() {
  std::stringstream ss;
  HuffmanTree tree = getAlphabeticTree();
  BitWriter bw(ss);

  // a
  bw.writeBit(0);

  // b
  bw.writeBit(1);
  bw.writeBit(0);

  // c
  bw.writeBit(1);
  bw.writeBit(1);
  bw.writeBit(0);

  // d
  bw.writeBit(1);
  bw.writeBit(1);
  bw.writeBit(1);
  bw.writeBit(0);

  // e
  bw.writeBit(1);
  bw.writeBit(1);
  bw.writeBit(1);
  bw.writeBit(1);
  bw.writeBit(0);

  // f
  bw.writeBit(1);
  bw.writeBit(1);
  bw.writeBit(1);
  bw.writeBit(1);
  bw.writeBit(1);
  bw.writeBit(0);

  // g
  bw.writeBit(1);
  bw.writeBit(1);
  bw.writeBit(1);
  bw.writeBit(1);
  bw.writeBit(1);
  bw.writeBit(1);
  bw.writeBit(0);

  // h
  bw.writeBit(1);
  bw.writeBit(1);
  bw.writeBit(1);
  bw.writeBit(1);
  bw.writeBit(1);
  bw.writeBit(1);
  bw.writeBit(1);
  bw.writeBit(0);

  bw.flush();

  BitReader br(ss);
  DataReader dr(tree, ss);

  assert(dr.readChar() == 'a');
  assert(dr.readChar() == 'b');
  assert(dr.readChar() == 'c');
  assert(dr.readChar() == 'd');
  assert(dr.readChar() == 'e');
  assert(dr.readChar() == 'f');
  assert(dr.readChar() == 'g');
  assert(dr.readChar() == 'h');
}

int main() {
  testAlphabeticTreeCodeLen();
  testBitReader();
  testBitWriter();
  testDataWriter();
  testDataReader();
  return 0;
}
