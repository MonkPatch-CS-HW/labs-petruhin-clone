#ifndef BIT_WRITER_HPP
#define BIT_WRITER_HPP

#include <fstream>
#include <string>

class BitWriter {
private:
  std::ostream &_out;
  int _bitsLeft;
  unsigned char _chunk;
  size_t _bytesWritten;

  void writeNext();

public:
  BitWriter(std::ostream &out);

  void writeBit(unsigned char bit);

  size_t flush();
};

#endif
