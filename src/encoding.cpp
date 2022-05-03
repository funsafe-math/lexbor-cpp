#include "encoding.h"
#include "exception.h"

namespace lexbor {

encoding::encoding() {
  auto status = lxb_html_encoding_init(&val);
  if (status != LXB_STATUS_OK)
    throw exception(status);
}

encoding::~encoding() {
  lxb_html_encoding_destroy(&val, false);
}

void encoding::determine(string_view html) {
  auto *start = html.data();
  auto *end = html.data() + html.size();
  auto status = lxb_html_encoding_determine(&val, start, end);
  if (status != LXB_STATUS_OK) {
    throw exception(status);
  }
}

string_view encoding::meta_entry(size_t idx) {
  auto *entry = lxb_html_encoding_meta_entry(&val, idx);
  if (entry == nullptr)
    return "";

  string_view sv(entry->name, (entry->end - entry->name));
  return sv;
}

} // namespace lexbor
