#pragma once
#include "base.h"
#include "utils.h"
#include <iostream>
#include <lexbor/dom/interfaces/node.h>
#include <lexbor/html/node.h>

namespace lexbor {
class document;

class node : public base {
public:
  node(lxb_dom_node_t *n);
  void serialize() const;

  static node interface_create(document doc);
  node interface_destroy();
  node destroy();
  node destroy_deep();
  const string_view name() const;

  void insert_child(node node);
  void insert_before(node node);
  void insert_after(node node);

  void remove();

protected:
  node() = default;

private:
  auto &get_ptr() { return get_ptr_impl<lxb_dom_node_t>(); }
  auto &get_ptr() const { return get_ptr_impl<lxb_dom_node_t>(); }
};

class text_node : public node {
private:
  auto &get_ptr() { return get_ptr_impl<lxb_dom_text_t>(); }

public:
  text_node(lxb_dom_text_t *t);
  operator lxb_dom_text_t *() { return get_ptr(); }
};

} // namespace lexbor
