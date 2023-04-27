#ifndef BINARY_READER_HPP
#define BINARY_READER_HPP
#include <fstream>
#include <string>

class BinaryReader {
private:
  std::ifstream _fin;
  int _bitsLeft;
  int _bitsStrip;
  bool _noRead;
  unsigned char _chunk;

public:
  BinaryReader(std::string filename, int bitsStrip = 0);

  unsigned char readByte();
  unsigned char readBit();

  bool tryReadByte(unsigned char &byte);
  bool tryReadBit(unsigned char &bit);
};

#endif
