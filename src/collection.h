#pragma once
#include "document.h"
#include "element.h"
#include <lexbor/dom/collection.h>

namespace lexbor {

class collection
{
public:
  collection(document &document, size_t start_list_size = 16);
  size_t length() const;
  lexbor::element at(size_t index);
  const lexbor::element at(size_t index) const;
  void clean();

  // TODO: collection can only be moved
  collection(collection &) = delete;
  collection(collection &&);
  ~collection();

  class element_iterator
      // Can be made into bidirectional iterator
      : public std::iterator<std::random_access_iterator_tag, // category
                             element,                         // value type
                             long,                            // difference type
                             const lxb_dom_element_t *,       // pointer type
                             element                          // reference
                             > {

    size_t idx;
    collection *col = nullptr;
    mutable lxb_dom_element_t *val = nullptr;

  public:
    explicit element_iterator(collection *_col, size_t ix)
        : idx(ix), col(_col) {
    }
    element_iterator &operator++();
    element_iterator &operator--();
    element_iterator operator++(int);
    bool operator==(element_iterator other) const;
    bool operator!=(element_iterator other) const;

    const element &operator*() const;
    ;
  };
  element_iterator begin();
  element_iterator end();

  operator lxb_dom_collection_t *() { return ptr; }

  friend class element;

protected:
  lxb_dom_collection_t *ptr = nullptr;
};

} // namespace lexbor
