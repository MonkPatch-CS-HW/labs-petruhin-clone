#include <cstring>
#include <fstream>
#include <iostream>

#include "CliArguments.hpp"
#include "HuffmanCompressor.hpp"
#include "HuffmanTree.hpp"

using namespace std;

int main(int argc, char **argv) {
  HuffmanCompressor hc;
  CliArguments args;

  HuffmanCompressor::CompressorStats stats;
  try {
    args.parse(argc, argv);
  } catch (std::exception &ex) {
    std::cerr << "error parsing arguments: " << ex.what() << std::endl;
    return 1;
  }

  if (args.inputFile.size() == 0) {
    std::cerr << "specify input file with -f or --file" << std::endl;
    return 1;
  }

  if (args.outputFile.size() == 0) {
    std::cerr << "specify output file with -o or --output" << std::endl;
    return 1;
  }

  std::ifstream fin(args.inputFile);
  std::ofstream fout(args.outputFile);

  if (!fin.is_open()) {
    std::cerr << "error opening input file" << std::endl;
    return 1;
  }

  if (!fout.is_open()) {
    std::cerr << "error opening output file" << std::endl;
    return 1;
  }

  switch (args.mode) {
  case CliArguments::MODE_COMPRESS:
    try {
      stats = hc.compress(fin, fout);
    } catch (std::exception &ex) {
      std::cerr << "error compressing file: " << ex.what() << std::endl;
      return 1;
    }
    break;
  case CliArguments::MODE_DECOMPRESS:
    try {
      stats = hc.decompress(fin, fout);
    } catch (std::exception &ex) {
      std::cerr << "error decompressing file: " << ex.what() << std::endl;
      return 1;
    }
    break;
  default:
    std::cerr << "specify mode with -c or -u" << std::endl;
    return 1;
  }

  std::cout << stats.sourceSize << std::endl
            << stats.processedSize << std::endl
            << stats.metadataSize << std::endl;

  return 0;
}
