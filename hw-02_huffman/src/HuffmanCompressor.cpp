#include <iostream>

#include "exceptions.hpp"
#include "BitReader.hpp"
#include "BitWriter.hpp"
#include "DataReader.hpp"
#include "DataWriter.hpp"
#include "HuffmanCompressor.hpp"
#include "HuffmanTree.hpp"

HuffmanCompressor::CompressorStats
HuffmanCompressor::compress(std::istream &in, std::ostream &out) {
  in.seekg(0, std::ios::end);
  size_t size = in.tellg();
  in.seekg(0, std::ios::beg);

  std::vector<char> buffer(size);
  if (!in.read(buffer.data(), size))
    throw IOException("could not read from file input");

  return compress(buffer, out);
}

HuffmanCompressor::CompressorStats
HuffmanCompressor::compress(std::vector<char> &buffer, std::ostream &out) {
  HuffmanTree ht = HuffmanTree::fromBuffer(buffer);
  std::vector<char> table = ht.normalize();

  size_t size = buffer.size();

  out.write((char *)table.data(), 256);
  out.write((char *)&size, sizeof(size_t));

  BitWriter bw(out);
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
HuffmanCompressor::decompress(std::istream &in, std::ostream &out) {
  std::vector<char> buffer;
  CompressorStats result = decompress(in, buffer);

  if (!out.write(buffer.data(), buffer.size()))
    throw IOException("could not write to file output");

  return result;
}

HuffmanCompressor::CompressorStats
HuffmanCompressor::decompress(std::istream &in, std::vector<char> &buffer) {
  size_t size;
  std::vector<char> table(256);

  in.read((char *)table.data(), 256);
  in.read((char *)&size, sizeof(size_t));

  buffer = std::vector<char>(size);

  HuffmanTree ht = HuffmanTree::fromTable(table);

  BitReader br(in);
  DataReader dr(ht, br);

  for (size_t i = 0; i < size; i++)
    buffer[i] = dr.readChar();

  return CompressorStats{
      .sourceSize = dr.flush(),
      .processedSize = size,
      .metadataSize = 256 + sizeof(size_t),
  };
}
