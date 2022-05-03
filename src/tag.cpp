#include "tag.h"

namespace lexbor {

bool tag::is_void() { return lxb_html_tag_is_void(m_tag_id); }

const lxb_html_tag_fixname_t *tag::fixname_svg() {
  return lxb_html_tag_fixname_svg(m_tag_id);
}

} // namespace lexbor
