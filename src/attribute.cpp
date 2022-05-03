#include "attribute.h"
#include "document.h"

namespace lexbor {

const string_view attribute::qualified_name() {
  size_t tmp_len;
  auto *name = lxb_dom_attr_qualified_name(ptr, &tmp_len);
  if (name == nullptr) {
    return "";
  }
  return string_view(name, tmp_len);
}

const string_view attribute::value() {
  size_t tmp_len;
  auto *name = lxb_dom_attr_value(ptr, &tmp_len);
  if (name == nullptr) {
    return "";
  }
  return string_view(name, tmp_len);
}

void attribute::set_value(const string_view value) {
  auto status = lxb_dom_attr_set_value(ptr, value.data(), value.size());
  if (status != LXB_STATUS_OK) {
    throw std::runtime_error("Failed to set attribute value");
  }
}

attribute attribute::interface_create(lexbor::document document) {
  return lxb_dom_attr_interface_create(document);
}

attribute attribute::interface_destroy() {
  return lxb_dom_attr_interface_destroy(*this);
}

void attribute::set_existing_value(const string_view value) {
  auto status =
      lxb_dom_attr_set_existing_value(*this, value.data(), value.size());
  throw_on_bad(status, "Failed to set attribute existing value");
}

bool attribute::operator==(attribute second) {
  return lxb_dom_attr_compare(*this, second);
}

const string_view attribute::local_name() {
  size_t len;
  auto *str = lxb_dom_attr_local_name(*this, &len);
  if (str == nullptr)
    throw std::runtime_error("Failed to get attribute local name");
  return string_view(str, len);
}

void attribute::set_name(const string_view localname, bool to_lowercase) {

  auto status = lxb_dom_attr_set_name(*this, localname.data(), localname.size(),
                                      to_lowercase);
  if (status != LXB_STATUS_OK) {
    throw std::runtime_error("Failed to set attribute name");
  }
}

} // namespace lexbor
