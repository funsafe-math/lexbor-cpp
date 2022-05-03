#include "element.h"
#include "collection.h"

namespace lexbor {

void element::elements_by_tag_name(collection &collection,
                                   const string_view qualified_name) {
  auto status = lxb_dom_elements_by_tag_name(
      get_ptr(), collection.ptr, qualified_name.data(), qualified_name.size());

  if (status != LXB_STATUS_OK) {
    throw std::runtime_error("Failed to find elements by tag name");
  }
}

void element::elements_by_class_name(collection &collection,
                                     const string_view class_name) {
  auto status = lxb_dom_elements_by_class_name(
      get_ptr(), collection.ptr, class_name.data(), class_name.size());
  throw_on_bad(status, "Failed to find elements by class name");
}

template <typename funcT>
void element::find_elements(collection &collection,
                            const string_view qualified_name,
                            const string_view value, bool case_insensitive,
                            funcT lxb_func) {

  throw_on_bad(lxb_func(get_ptr(), collection, qualified_name.data(),
                        qualified_name.size(), value.data(), value.size(),
                        case_insensitive),
               "Failed to find elements by attribute");
}

void element::elements_by_attr(collection &collection,
                               const string_view qualified_name,
                               const string_view value, bool case_insensitive) {
  throw_on_bad(lxb_dom_elements_by_attr(get_ptr(), collection,
                                        qualified_name.data(),
                                        qualified_name.size(), value.data(),
                                        value.size(), case_insensitive),
               "Failed to find elements by attribute");
}

void element::elements_by_attr_begin(collection &collection,
                                     const string_view qualified_name,
                                     const string_view value,
                                     bool case_insensitive) {
  find_elements(collection, qualified_name, value, case_insensitive,
                lxb_dom_elements_by_attr_begin);
}

void element::elements_by_attr_end(collection &collection,
                                   const string_view qualified_name,
                                   const string_view value,
                                   bool case_insensitive) {
  find_elements(collection, qualified_name, value, case_insensitive,
                lxb_dom_elements_by_attr_end);
}

void element::elements_by_attr_contain(collection &collection,
                                       const string_view qualified_name,
                                       const string_view value,
                                       bool case_insensitive) {
  find_elements(collection, qualified_name, value, case_insensitive,
                lxb_dom_elements_by_attr_contain);
}

attribute element::set_attribute(const string_view qualified_name,
                                 const string_view value) {

  auto *attr = lxb_dom_element_set_attribute(get_ptr(), qualified_name.data(),
                                             qualified_name.size(),
                                             value.data(), value.size());
  if (attr == NULL) {
    throw std::runtime_error("Failed to create and append new attribute");
  }
  return attr;
}

bool element::has_attribute(const string_view qualified_name) {

  return lxb_dom_element_has_attribute(get_ptr(), qualified_name.data(),
                                       qualified_name.size());
}

const string_view element::get_attribute(const string_view qualified_name) {
  size_t val_len;
  auto *value = lxb_dom_element_get_attribute(get_ptr(), qualified_name.data(),
                                              qualified_name.size(), &val_len);
  if (value == nullptr) {
    throw std::runtime_error("Failed to get attribute value by qualified name");
  }
  return string_view(value, val_len);
}

attribute element::attr_by_name(const string_view qualified_name) {
  return attribute(lxb_dom_element_attr_by_name(
      get_ptr(), qualified_name.data(), qualified_name.size()));
}

attribute element::first_attribute() {
  return lxb_dom_element_first_attribute(get_ptr());
}

void element::remove_attribute(const string_view qualified_name) {
  auto status = lxb_dom_element_remove_attribute(
      get_ptr(), qualified_name.data(), qualified_name.size());
  if (status != LXB_STATUS_OK) {
    throw std::runtime_error("Failed to remove attribute");
  }
}

element element::inner_html_set(string_view html) {
  auto *ret = lxb_html_element_inner_html_set(*this, html.data(), html.size());

  if (ret == nullptr) {
    throw std::runtime_error("Failed to parse innerHTML");
  }
  return ret;
}

element::attr_iterator element::begin() {
  return attr_iterator(first_attribute());
}

element::attr_iterator element::end() { return attr_iterator(nullptr); }

const attribute &element::attr_iterator::operator*() const {
  static_assert(sizeof(lexbor::attribute) == sizeof(val) &&
                    alignof(lexbor::attribute) == alignof(decltype(val)),
                "Lexbor attribute must be convertible to a attr pointer!");
  return reinterpret_cast<const attribute &>(val);
}

} // namespace lexbor
