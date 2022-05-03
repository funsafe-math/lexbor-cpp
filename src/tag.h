#pragma once
#include "utils.h"
#include <lexbor/html/tag.h>

namespace lexbor {

class tag
{
public:
  tag(lxb_tag_id_t tag_id) : m_tag_id(tag_id) {}
  tag() = default;

  tag operator++(int) {
    tag ret(*this);
    m_tag_id++;
    return ret;
  }

  operator lxb_tag_id_t() { return m_tag_id; }

  bool is_void();
  const lxb_html_tag_fixname_t *fixname_svg();

protected:
  lxb_tag_id_t m_tag_id = LXB_TAG_A;
};

} // namespace lexbor
