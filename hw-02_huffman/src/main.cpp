#include <cstring>
#include <fstream>
#include <iostream>

#include "CliArguments.hpp"
#include "HuffmanCompressor.hpp"

using namespace std;

int main(int argc, char **argv) {
  HuffmanCompressor hc;
  CliArguments args;

  HuffmanCompressor::CompressorStats stats;
  args.parse(argc, argv);

  if (args.inputFile.size() == 0) {
    std::cerr << "Specify input file with -f or --file" << std::endl;
    return 1;
  }

  if (args.outputFile.size() == 0) {
    std::cerr << "Specify output file with -o or --output" << std::endl;
    return 1;
  }

  std::ifstream fin(args.inputFile);
  std::ofstream fout(args.outputFile);

  switch (args.mode) {
  case CliArguments::MODE_COMPRESS:
    stats = hc.compress(fin, fout);
    break;
  case CliArguments::MODE_DECOMPRESS:
    stats = hc.decompress(fin, fout);
    break;
  default:
    std::cerr << "Specify mode with -c or -u" << std::endl;
    return 1;
  }

  std::cout << stats.sourceSize << std::endl
            << stats.processedSize << std::endl
            << stats.metadataSize << std::endl;

  return 0;
}
