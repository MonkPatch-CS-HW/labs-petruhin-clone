#include <iostream>

#include "BitReader.hpp"
#include "BitWriter.hpp"
#include "DataReader.hpp"
#include "DataWriter.hpp"
#include "HuffmanCompressor.hpp"
#include "HuffmanTree.hpp"

HuffmanCompressor::CompressorStats
HuffmanCompressor::compress(std::ifstream &fin, std::ofstream &fout) {
  fin.seekg(0, std::ios::end);
  size_t size = fin.tellg();
  fin.seekg(0, std::ios::beg);

  std::vector<char> buffer(size);
  if (!fin.read(buffer.data(), size))
    throw std::logic_error(std::string("TODO"));

  return compress(buffer, fout);
}

HuffmanCompressor::CompressorStats
HuffmanCompressor::compress(std::vector<char> &buffer, std::ofstream &fout) {
  HuffmanTree ht = HuffmanTree::fromBuffer(buffer);
  std::vector<char> table = ht.generateTable();
  size_t size = buffer.size();

  fout.write((char *)table.data(), 256);
  fout.write((char *)&size, sizeof(size_t));

  BitWriter bw(fout);
  DataWriter dw(ht, bw);

  for (size_t i = 0; i < size; i++)
    dw.writeChar(buffer[i]);

  return CompressorStats{
      .sourceSize = size,
      .processedSize = dw.flush(),
      .metadataSize = 256 + sizeof(size_t),
  };
}

HuffmanCompressor::CompressorStats
HuffmanCompressor::decompress(std::ifstream &fin, std::ofstream &fout) {
  fin.seekg(0, std::ios::beg);

  std::vector<char> buffer;
  CompressorStats result = decompress(fin, buffer);

  fout.write(buffer.data(), buffer.size());

  return result;
}

HuffmanCompressor::CompressorStats
HuffmanCompressor::decompress(std::ifstream &fin, std::vector<char> &buffer) {
  size_t size;
  std::vector<char> table(256);

  fin.read((char *)table.data(), 256);
  fin.read((char *)&size, sizeof(size_t));

  buffer = std::vector<char>(size);

  HuffmanTree ht = HuffmanTree::fromTable(table);
  BitReader br(fin);
  DataReader dr(ht, br);

  for (size_t i = 0; i < size; i++)
    buffer[i] = dr.readChar();

  return CompressorStats{
      .sourceSize = dr.flush(),
      .processedSize = size,
      .metadataSize = 256 + sizeof(size_t),
  };
}
