#include "exceptions.hpp"
#include <sstream>

HuffmanNodeException::HuffmanNodeException(const char *what)
    : std::runtime_error(what) {}

IOException::IOException(const char *what) : std::runtime_error(what) {}

EncodingException::EncodingException(const char *what)
    : std::logic_error(what) {}

EncodingException::EncodingException(const char *what, unsigned char ch)
    : std::logic_error("") {
  std::stringstream ss;
  ss << what << " (inserting symbol with code: " << (int)ch << ")";
  _str = ss.str();
}

const char *EncodingException::what() const noexcept { return _str.c_str(); }

DecodingException::DecodingException(const char *what) : std::logic_error(what) {}
