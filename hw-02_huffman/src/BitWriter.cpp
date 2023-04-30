#include <exception>
#include <iostream>
#include <stdexcept>

#include "BitWriter.hpp"

BitWriter::BitWriter(std::ofstream &fout)
    : _fout(fout), _bitsLeft(0), _chunk(0), _bytesWritten(0) {}

void BitWriter::writeNext() {
  _fout.write((char *)&_chunk, sizeof(unsigned char));

  if (!_fout.good())
    throw std::runtime_error("could not write chunk");

  _bitsLeft = 0;
  _chunk = 0;

  _bytesWritten++;
}

size_t BitWriter::flush() {
  if (_bitsLeft != 0)
    writeNext();

  size_t result = _bytesWritten;
  _bytesWritten = 0;

  return result;
}

void BitWriter::writeBit(unsigned char bit) {
  _bitsLeft = (_bitsLeft - 1 + 8) % 8;
  _chunk |= bit << _bitsLeft;

  if (_bitsLeft == 0)
    writeNext();
}

void BitWriter::close() { _fout.close(); }
