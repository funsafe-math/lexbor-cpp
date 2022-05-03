#pragma once
#include "utils.h"
#include <lexbor/dom/interfaces/attr.h>
#include <stdexcept>
#include <string_view>

namespace lexbor {
class document;

class attribute
{
public:
  attribute(lxb_dom_attr_t *attribute) : ptr(attribute) {}
  const string_view qualified_name();
  const string_view local_name();
  const string_view value();
  void set_name(const string_view localname, bool to_lowercase);
  void set_value(const string_view value);

  static attribute interface_create(document document);
  attribute interface_destroy();
  void set_existing_value(const string_view value);
  bool operator==(attribute second);

  friend class element;

protected:
  operator lxb_dom_attr_t *() { return ptr; }

private:
  lxb_dom_attr_t *ptr = nullptr;
};

} // namespace lexbor
