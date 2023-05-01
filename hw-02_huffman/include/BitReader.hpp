#ifndef BIT_READER_HPP
#define BIT_READER_HPP

#include <fstream>
#include <string>

class BitReader {
private:
  std::istream &_in;
  int _bitsLeft;
  unsigned char _chunk;
  size_t _bytesRead;

  void readNext();

public:
  BitReader(std::istream &in);

  unsigned char readBit();

  size_t flush();
};

#endif
