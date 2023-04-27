#include "BinaryReader.hpp"
#include "BinaryWriter.hpp"
#include "HuffmanNode.hpp"
#include "HuffmanTree.hpp"
#include <iostream>

using namespace std;

int main() {
  {
    BinaryWriter bw("fileo.bin");
    bw.writeBit(0);
    bw.writeBit(1);
    bw.writeBit(0);
    bw.writeBit(1);
    bw.writeByte(255);
    bw.writeBit(0);
    bw.writeBit(1);
    bw.writeBit(0);
    bw.writeBit(1);
  }

  BinaryReader br("fileo.bin", 3);
  unsigned char bit;
  while (br.tryReadBit(bit)) {
    std::cout << (int)bit;
  }
  std::cout << std::endl;
  // BinaryWriter bw("fileo.bin");
  // BinaryReader br("file.bin");
  // char table[256] = {
  //     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  //     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  //     5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  //     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  //     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 6, 0, 0, 6, 0, 0, 0, 4, 0,
  //     0, 5, 0, 0, 5, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  //     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  //     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  //     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  //     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  //     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  //     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  // };
  // HuffmanTree *tree =
  //     HuffmanTree::fromText("hello, "
  //                           "worlddddddddddddddddddd!!!!!!!!!!!!!!!!!!!!!!!!!!!"
  //                           "!!!!!!!!!!!!!!!!!!!!!!!!!");
  // HuffmanTree *tree = HuffmanTree::fromTable(table);

  // tree->print();
  // tree->printTable();
  // delete tree;
  return 0;
}
