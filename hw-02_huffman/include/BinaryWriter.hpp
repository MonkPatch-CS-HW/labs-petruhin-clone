#ifndef BINARY_WRITER_HPP
#define BINARY_WRITER_HPP
#include <fstream>
#include <string>

class BinaryWriter {
private:
  std::ofstream _fout;
  int _bitsLeft;
  int _bitsStrip;
  bool _noWrite;
  unsigned char _chunk;

public:
  BinaryWriter(std::string filename);

  void writeByte(unsigned char byte);
  void writeBit(unsigned char bit);

  bool tryWriteByte(unsigned char byte);
  bool tryWriteBit(unsigned char bit);

  void close();
};

#endif
