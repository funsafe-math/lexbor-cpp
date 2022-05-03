#pragma once
#include "attribute.h"
#include "utils.h"
#include <lexbor/dom/interface.h>
#include <lexbor/dom/interfaces/element.h>
#include <lexbor/html/interfaces/element.h>
#include <node.h>
#include <stdexcept>
#include <string_view>

namespace lexbor {
class collection;
class attribute;

class element : public node {
protected:
  auto &get_ptr() { return get_ptr_impl<lxb_dom_element>(); }

public:
  element(lxb_dom_element_t *element) {
    if (element == nullptr)
      throw std::runtime_error("Attempted to create element with nullptr");
    get_ptr() = element;
  }

  element(lxb_html_element_t *element) {
    if (element == nullptr)
      throw std::runtime_error("Attempted to create element with nullptr");
    get_ptr_impl<lxb_html_element_t>() = element;
  }

  void elements_by_tag_name(collection &collection,
                            const string_view qualified_name);

  void elements_by_class_name(collection &collection,
                              const string_view class_name);

  void elements_by_attr(collection &collection,
                        const string_view qualified_name,
                        const string_view value, bool case_insensitive);

  void elements_by_attr_begin(collection &collection,
                              const string_view qualified_name,
                              const string_view value,
                              bool case_insensitive = false);

  void elements_by_attr_end(collection &collection,
                            const string_view qualified_name,
                            const string_view value,
                            bool case_insensitive = false);

  void elements_by_attr_contain(collection &collection,
                                const string_view qualified_name,
                                const string_view value,
                                bool case_insensitive = false);

  attribute set_attribute(const string_view qualified_name,
                          const string_view value);
  [[nodiscard]] bool has_attribute(const string_view qualified_name);
  const string_view get_attribute(const string_view qualified_name);
  attribute attr_by_name(const string_view qualified_name);

  attribute first_attribute();
  // TODO last attribute, next attribute etc.

  void remove_attribute(const string_view qualified_name);

  element inner_html_set(string_view html);

  operator lxb_html_element_t *() {
    return reinterpret_cast<lxb_html_element_t *>(get_ptr());
  }

  class attr_iterator
      // Can be made into bidirectional iterator
      : public std::iterator<std::forward_iterator_tag, // category
                             attribute,                 // value type
                             long,                      // difference type
                             const lxb_dom_attr *,      // pointer type
                             attribute                  // reference
                             > {

    lxb_dom_attr_t *val = nullptr;

  public:
    explicit attr_iterator(lxb_dom_attr_t *first) : val(first) {}
    attr_iterator &operator++() {
      val = lxb_dom_element_next_attribute(val);
      return *this;
    }
    attr_iterator &operator--() {
      val = lxb_dom_element_prev_attribute(val);
      return *this;
    }
    attr_iterator operator++(int) {
      attr_iterator retval = *this;
      ++(*this);
      return retval;
    }
    bool operator==(attr_iterator other) const { return val == other.val; }
    bool operator!=(attr_iterator other) const { return !(*this == other); }

    const attribute &operator*() const;
  };
  attr_iterator begin();
  attr_iterator end();

protected:
  template <typename funcT>
  void find_elements(collection &collection, const string_view qualified_name,
                     const string_view value, bool case_insensitive,
                     funcT lxb_func);
};

} // namespace lexbor
