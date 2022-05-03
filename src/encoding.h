#pragma once
#include "base.h"
#include "utils.h"
#include <lexbor/html/encoding.h>

namespace lexbor {

class encoding {
private:
  lxb_html_encoding_t val;

public:
  encoding();
  ~encoding();

  void determine(string_view html);
  string_view meta_entry(size_t idx);
};

} // namespace lexbor
