#include <exception>
#include <iostream>

#include "BitReader.hpp"

BitReader::BitReader(std::ifstream &fin)
    : _fin(fin), _bitsLeft(0), _noRead(false), _chunk(0) {}

void BitReader::readNext() {
  _fin.read((char *)&_chunk, sizeof(unsigned char));

  if (!_fin.good())
    _noRead = true;

  _bitsLeft = 8;
}

void BitReader::flush() {
  _bitsLeft = 0;
}

bool BitReader::tryReadBit(unsigned char &bit) {
  if (_noRead)
    return false;

  if (_bitsLeft == 0)
    readNext();

  _bitsLeft = (_bitsLeft - 1 + 8) % 8;
  bit = (_chunk >> _bitsLeft) & 0b1;

  std::cout << "next bit = " << bit << std::endl;

  return true;
}

unsigned char BitReader::readBit() {
  unsigned char bit;
  if (tryReadBit(bit))
    return bit;

  throw std::logic_error("TODO");
}

void BitReader::close() { _fin.close(); }
