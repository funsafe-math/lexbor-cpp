#include "node.h"
#include "document.h"
#include <lexbor/html/serialize.h>

namespace lexbor {

node::node(lxb_dom_node_t *n) {
  if (n == nullptr) {
    throw std::runtime_error("Attempted to initialize node with a nullptr");
  }
  get_ptr() = n;
}

void node::serialize() const {
  lxb_status_t status;
  auto callback = [](const lxb_char_t *data, size_t len, void *ctx) {
    printf("%.*s", (int)len, (const char *)data);
    return lxb_status_t(LXB_STATUS_OK);
  };

  status = lxb_html_serialize_pretty_tree_cb(
      get_ptr(), LXB_HTML_SERIALIZE_OPT_UNDEF, 0, callback, NULL);
  if (status != LXB_STATUS_OK) {
    throw std::runtime_error("Failed to serialization HTML tree");
  }
}

node node::interface_create(document doc) {
  return lxb_dom_node_interface_create(&doc.get_ptr()->dom_document);
}

node node::interface_destroy() {
  return lxb_dom_node_interface_destroy(get_ptr());
}

node node::destroy() { return lxb_dom_node_destroy(get_ptr()); }

node node::destroy_deep() { return lxb_dom_node_destroy_deep(get_ptr()); }

const string_view node::name() const {
  size_t len;
  auto *str = lxb_dom_node_name(get_ptr(), &len);
  if (str == nullptr)
    throw std::runtime_error("Failed to get node name");
  return string_view(str, len);
}

void node::insert_child(node node) {
  lxb_dom_node_insert_child(get_ptr(), node.get_ptr());
}

void node::insert_before(node node) {
  lxb_dom_node_insert_before(get_ptr(), node.get_ptr());
}

void node::insert_after(node node) {
  lxb_dom_node_insert_after(get_ptr(), node.get_ptr());
}

void node::remove() { lxb_dom_node_remove(get_ptr()); }

text_node::text_node(lxb_dom_text_t *t) { get_ptr() = t; }

} // namespace lexbor
