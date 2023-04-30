#ifndef BIT_WRITER_HPP
#define BIT_WRITER_HPP

#include <fstream>
#include <string>

class BitWriter {
private:
  std::ofstream &_fout;
  int _bitsLeft;
  bool _noWrite;
  unsigned char _chunk;
  size_t _bytesWritten;

  void writeNext();

public:
  BitWriter(std::ofstream &fout);

  bool tryWriteBit(unsigned char bit);
  void writeBit(unsigned char bit);

  size_t flush();

  void close();
};

#endif
