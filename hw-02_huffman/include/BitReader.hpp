#ifndef BIT_READER_HPP
#define BIT_READER_HPP

#include <fstream>
#include <string>

class BitReader {
private:
  std::ifstream &_fin;
  int _bitsLeft;
  bool _noRead;
  unsigned char _chunk;

public:
  BitReader(std::ifstream &fin);

  bool tryReadBit(unsigned char &bit);
  unsigned char readBit();

  void flush();

  void close();
};

#endif
