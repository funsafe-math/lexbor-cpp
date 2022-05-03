#pragma once
#include "element.h"
#include <lexbor/html/interface.h>

namespace lexbor {

class body_element : public element {
public:
  body_element(lxb_html_body_element_t *body)
      : element(reinterpret_cast<lxb_dom_element_t *>(body)) {}

protected:
  lxb_html_body_element_t *&get_ptr() {
    return reinterpret_cast<lxb_html_body_element_t *&>(element::get_ptr());
  }
};

} // namespace lexbor
