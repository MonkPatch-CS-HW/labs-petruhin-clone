#ifndef CLI_ARGUMENTS_HPP
#define CLI_ARGUMENTS_HPP

#include <cstring>
#include <string>

struct CliArguments {
public:
  enum Mode {
    MODE_IDLE,
    MODE_COMPRESS,
    MODE_DECOMPRESS,
  };

  Mode mode;
  std::string inputFile;
  std::string outputFile;

  CliArguments();

  void parse(int argc, char **argv);

private:
  enum ArgumentType {
    ARGUMENT_IDLE,
    ARGUMENT_INPUT,
    ARGUMENT_OUTPUT,
  };
};

#endif
