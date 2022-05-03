#include "hash.h"

namespace lexbor {

void hash::create() { ptr = lexbor_hash_create(); }

const string_view tags_hash::name_by_id(lxb_tag_id_t tag_id) {
  size_t len;
  auto *str = lxb_tag_name_by_id(ptr, tag_id, &len);
  if (str == nullptr)
    throw std::runtime_error("Failed to get tag name by id");
  return string_view(str, len);
}

} // namespace lexbor
