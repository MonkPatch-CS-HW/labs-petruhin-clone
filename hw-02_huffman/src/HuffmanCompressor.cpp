#include "HuffmanCompressor.hpp"
#include "BitReader.hpp"
#include "BitWriter.hpp"
#include "DataReader.hpp"
#include "DataWriter.hpp"
#include "HuffmanTree.hpp"

void HuffmanCompressor::compress(char *buffer, size_t n, std::ofstream &fout) {
  HuffmanTree *ht_ = HuffmanTree::fromText(buffer, n);

  unsigned char *table = ht_->generateTable();
  HuffmanTree *ht = HuffmanTree::fromTable(table);

  fout.write((char *)table, 256);
  fout.write((char *)&n, sizeof(size_t));
  BitWriter bw(fout);
  DataWriter dw(ht, bw);
  for (size_t i = 0; i < n; i++)
    dw.writeChar(buffer[i]);
  dw.flush();
  delete ht;
}

size_t HuffmanCompressor::decompress(char *&buffer,
                                     std::ifstream &fin) {
  size_t n;
  unsigned char *table = new unsigned char[256];
  fin.read((char *)table, 256);
  fin.read((char *)&n, sizeof(size_t));
  buffer = new char[n];
  HuffmanTree *ht = HuffmanTree::fromTable(table);
  BitReader br(fin);
  DataReader dr(ht, br);
  for (size_t i = 0; i < n; i++)
    buffer[i] = dr.readChar();
  dr.flush();
  delete ht;
  delete[] table;
  return n;
}
