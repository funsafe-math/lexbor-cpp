#pragma once
#include "base.h"
#include "body_element.h"
#include "hash.h"
#include "node.h"
#include "utils.h"
#include <lexbor/html/html.h>
#include <memory>
#include <string_view>

namespace lexbor {
class node;

class document : public virtual node {
public:
  document();
  document(const string_view html);
  document(document &&other);

  ~document();

  document &operator=(document &other) = delete;

public:
  void parse(const string_view html);
  void parse_chunk_begin();
  void parse_chunk(const string_view chunk);
  void parse_chunk_end();

  const string_view title();
  const string_view title_raw();
  void title_set(const string_view new_title);

  tags_hash document_tags();
  lexbor::body_element body_element(void);

  element create_element(const string_view local_name,
                         void *reserved_for_opt = nullptr);

  text_node create_text_node(const string_view data);

  element lxb_dom_document_destroy_element(element elem);

  friend class collection;
  friend class node;

protected:
  auto &get_ptr() { return get_ptr_impl<lxb_html_document_t>(); }
  //  lxb_html_document_t *m_document = nullptr;
public:
  operator lxb_dom_document_t *() { return &get_ptr()->dom_document; }
  operator lxb_html_document_t *() { return get_ptr(); }

private:
  void create();
};

} // namespace lexbor
