#include <exception>

#include "BitWriter.hpp"

BitWriter::BitWriter(std::ofstream &fout)
    : _fout(fout), _bitsLeft(0), _noWrite(false), _chunk(0) {}

void BitWriter::flush() {
  _fout.write((char *)&_chunk, sizeof(unsigned char));

  if (!_fout.good())
    _noWrite = true;

  _bitsLeft = 8;
  _chunk = 0;
}

bool BitWriter::tryWriteBit(unsigned char bit) {
  if (_noWrite)
    return false;

  _bitsLeft = (_bitsLeft - 1 + 8) % 8;
  _chunk |= bit << _bitsLeft;

  if (_bitsLeft == 0) {
    flush();
  }

  return true;
}

void BitWriter::writeBit(unsigned char bit) {
  if (tryWriteBit(bit))
    return;

  throw std::logic_error("TODO");
}

void BitWriter::close() { _fout.close(); }
