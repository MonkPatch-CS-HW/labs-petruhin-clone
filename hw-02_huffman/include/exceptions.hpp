#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <stdexcept>

class HuffmanNodeException : public std::runtime_error {
public:
  HuffmanNodeException(const char *what);
};

class IOException : public std::runtime_error {
public:
  IOException(const char *what);
};

class EncodingException : public std::logic_error {
private:
  std::string _str;

public:
  EncodingException(const char *what);
  EncodingException(const char *what, unsigned char ch);

  const char *what() const noexcept override;
};

class DecodingException : public std::logic_error {
public:
  DecodingException(const char *what);
};

#endif
