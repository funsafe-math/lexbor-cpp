#pragma once
#include <exception>
#include <lexbor/core/base.h>

namespace lexbor {
class exception : public std::exception {
public:
  exception(lxb_status_t _code);
  lexbor_status_t code;
  virtual const char *what() final;
};

} // namespace lexbor
