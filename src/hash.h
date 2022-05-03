#pragma once
#include "utils.h"
#include <lexbor/core/hash.h>
#include <lexbor/tag/tag.h>
#include <stdexcept>

namespace lexbor {

class hash
{
public:
  hash(lexbor_hash_t *hash_p) : ptr(hash_p) {}

  void create();

  lxb_status_t init(size_t table_size, size_t struct_size);

  void clean(lexbor_hash_t *hash);

  lexbor_hash_t *hash_destroy(bool destroy_obj);

  void *hash_insert(const lexbor_hash_insert_t *insert, const string_view key);

  void *hash_insert_by_entry(lexbor_hash_entry_t *entry,
                             const lexbor_hash_search_t *search,
                             const string_view key);

  void remove(const lexbor_hash_search_t *search, const string_view key);

  void *hash_search(const lexbor_hash_search_t *search, const string_view key);

  void remove_by_hash_id(uint32_t id, const string_view key,
                         const lexbor_hash_cmp_f cmp_func);

  void *hash_search_by_hash_id(uint32_t id, const string_view key,
                               const lexbor_hash_cmp_f cmp_func);

  uint32_t make_id(const string_view key);

  uint32_t make_id_lower(const string_view key);

  uint32_t make_id_upper(const string_view key);

  lxb_status_t copy(lexbor_hash_entry_t *entry, const string_view key);

  lxb_status_t copy_lower(lexbor_hash_entry_t *entry, const string_view key);

  lxb_status_t copy_upper(lexbor_hash_entry_t *entry, const string_view key);

  lexbor_mraw_t *mraw(const lexbor_hash_t *hash);

  lxb_char_t *entry_str(const lexbor_hash_entry_t *entry);

  lxb_char_t *entry_str_set(lexbor_hash_entry_t *entry, lxb_char_t *data,
                            size_t length);

  //  void entry_str_free( entry_t *entry);

  //  entry_t *lexbor_hash_entry_create(lexbor_hash_t *hash);

  //  entry_t *lexbor_hash_entry_destroy( entry_t *entry);

  size_t entries_count(lexbor_hash_t *hash);

protected:
  lexbor_hash_t *ptr = nullptr;
};

class tags_hash : public hash {
public:
  using hash::hash;
  const string_view name_by_id(lxb_tag_id_t tag_id);
};

} // namespace lexbor
