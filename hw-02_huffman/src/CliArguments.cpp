#include <stdexcept>

#include "CliArguments.hpp"

CliArguments::CliArguments() : mode(MODE_IDLE) {}

void CliArguments::parse(int argc, char **argv) {
  ArgumentType argumentType = ARGUMENT_IDLE;

  for (int i = 0; i < argc; i++) {
    if (strcmp(argv[i], "-c") == 0) {
      mode = MODE_COMPRESS;
      continue;
    }

    if (strcmp(argv[i], "-u") == 0) {
      mode = MODE_DECOMPRESS;
      continue;
    }

    if (strcmp(argv[i], "-f") == 0 || strcmp(argv[i], "--file") == 0) {
      argumentType = ARGUMENT_INPUT;
      continue;
    }

    if (strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--output") == 0) {
      argumentType = ARGUMENT_OUTPUT;
      continue;
    }

    if (argumentType == ARGUMENT_INPUT) {
      inputFile = argv[i];
      argumentType = ARGUMENT_IDLE;
      continue;
    }

    if (argumentType == ARGUMENT_OUTPUT) {
      outputFile = argv[i];
      argumentType = ARGUMENT_IDLE;
      continue;
    }
  }
}
