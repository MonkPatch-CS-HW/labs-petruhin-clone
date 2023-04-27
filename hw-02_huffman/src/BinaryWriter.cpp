#include "BinaryWriter.hpp"
#include <exception>

BinaryWriter::BinaryWriter(std::string filename)
    : _fout(filename, std::ios::binary | std::ios::out), _bitsLeft(0),
      _bitsStrip(0), _noWrite(false), _chunk(0) {}

bool BinaryWriter::tryWriteByte(unsigned char byte) {
  if (_noWrite)
    return false;

  unsigned char toWrite = _chunk | (byte >> (8 - _bitsLeft));
  _chunk = byte << _bitsLeft;

  _fout.write((char *)&toWrite, sizeof(unsigned char));
  if (!_fout.good()) {
    _noWrite = true;
    return false;
  }

  return true;
}

void BinaryWriter::writeByte(unsigned char byte) {
  if (tryWriteByte(byte))
    return;

  throw std::logic_error("TODO");
}

bool BinaryWriter::tryWriteBit(unsigned char bit) {
  if (_noWrite)
    return false;

  _bitsLeft = (_bitsLeft - 1 + 8) % 8;
  _chunk |= bit << _bitsLeft;

  if (_bitsLeft == 0) {
    writeByte(_chunk);
    _chunk = 0;
  }

  return true;
}

void BinaryWriter::writeBit(unsigned char bit) {
  if (tryWriteBit(bit))
    return;

  throw std::logic_error("TODO");
}
