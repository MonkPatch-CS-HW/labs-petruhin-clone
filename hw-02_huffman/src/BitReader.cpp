#include <exception>
#include <iostream>

#include "BitReader.hpp"
#include "exceptions.hpp"

BitReader::BitReader(std::ifstream &fin)
    : _fin(fin), _bitsLeft(0), _chunk(0), _bytesRead(0) {}

void BitReader::readNext() {
  _fin.read((char *)&_chunk, sizeof(unsigned char));

  if (!_fin.good())
    throw IOException("could not read chunk");

  _bitsLeft = 0;

  _bytesRead++;
}

size_t BitReader::flush() {
  _bitsLeft = 0;

  size_t result = _bytesRead;
  _bytesRead = 0;

  return result;
}

unsigned char BitReader::readBit() {
  if (_bitsLeft == 0)
    readNext();

  _bitsLeft = (_bitsLeft - 1 + 8) % 8;

  return (_chunk >> _bitsLeft) & 0b1;
}

void BitReader::close() { _fin.close(); }
