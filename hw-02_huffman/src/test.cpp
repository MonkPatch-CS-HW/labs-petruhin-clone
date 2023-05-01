#include <assert.h>
#include <ctime>
#include <sstream>
#include <streambuf>
#include <vector>
#include <random>

#include "HuffmanCompressor.hpp"
#include "HuffmanTree.hpp"

std::mt19937 mt(time(nullptr));

void test_table() {
  std::vector<unsigned char> table = {
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 4, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 3, 4, 0, 0, 4, 0, 0, 0, 3, 0, 0, 3, 0, 0, 4, 0, 0, 0, 0, 4,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  };

  std::string text("hello, world!!!!!!!");

  std::vector<char> buffer(text.begin(), text.end());
  HuffmanTree ht = HuffmanTree::fromBuffer(buffer);

  assert(ht.getTable() == table);
}

void test_encoding_decoding() {
  std::vector<char> buffer(1024);
  std::vector<char> obuffer(1024);

  for (int i = 0; i < 256; i++)
    buffer[i] = mt();

  HuffmanCompressor hc;
  std::stringstream ss;

  hc.compress(buffer, ss);
  hc.decompress(ss, obuffer);

  assert(buffer == obuffer);
}

int main() {
  test_table();
  test_encoding_decoding();

  return 0;
}
