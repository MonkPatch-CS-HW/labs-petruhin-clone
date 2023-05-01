#ifndef HUFFMAN_COMPRESSOR_HPP
#define HUFFMAN_COMPRESSOR_HPP

#include <fstream>
#include <vector>

class HuffmanCompressor {
public:
  struct CompressorStats {
    size_t sourceSize;
    size_t processedSize;
    size_t metadataSize;
  };

  CompressorStats compress(std::istream &in, std::ostream &out) const;
  CompressorStats compress(std::vector<char> &buffer, std::ostream &out) const;

  CompressorStats decompress(std::istream &in, std::vector<char> &buffer) const;
  CompressorStats decompress(std::istream &in, std::ostream &out) const;
};

#endif
