#include "BinaryReader.hpp"
#include <exception>

BinaryReader::BinaryReader(std::string filename, int bitsStrip)
    : _fin(filename, std::ios::binary | std::ios::in), _bitsLeft(0),
      _bitsStrip(bitsStrip), _noRead(false), _chunk(0) {}

bool BinaryReader::tryReadByte(unsigned char &byte) {
  if (_noRead)
    return false;

  unsigned char oldChunk = _chunk;
  _fin.read((char *)&_chunk, sizeof(unsigned char));
  if (!_fin.good()) {
    _noRead = true;
    return false;
  }

  byte = (oldChunk << (8 - _bitsLeft)) | (_chunk >> _bitsLeft);
  if (_bitsLeft <= 0)
    _bitsLeft = 8;

  return true;
}

unsigned char BinaryReader::readByte() {
  unsigned char byte;
  if (tryReadByte(byte))
    return byte;

  throw std::logic_error("TODO");
}

bool BinaryReader::tryReadBit(unsigned char &bit) {
  bit = (_chunk >> --_bitsLeft) & 0b1;

  if (_noRead && _bitsLeft < _bitsStrip)
    return false;

  if (_bitsLeft == 0)
    readByte();

  return true;
}

unsigned char BinaryReader::readBit() {
  unsigned char bit;
  if (tryReadBit(bit))
    return bit;

  throw std::logic_error("TODO");
}
