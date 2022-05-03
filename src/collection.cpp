#include "collection.h"
#include <utility>

namespace lexbor {

collection::collection(document &document, size_t start_list_size) {
  auto *lxb_doc = document.get_ptr();
  ptr = lxb_dom_collection_make(&lxb_doc->dom_document, start_list_size);
  if (ptr == nullptr) {
    throw std::runtime_error("Failed to create collection");
  }
}

collection::collection(collection &&other)
    : ptr(std::exchange(other.ptr, nullptr)) {
}

size_t collection::length() const { return lxb_dom_collection_length(ptr); }

element collection::at(size_t index) {
  return lxb_dom_collection_element(ptr, index);
}

const element collection::at(size_t index) const {
  return lxb_dom_collection_element(ptr, index);
}

void collection::clean() { return lxb_dom_collection_clean(ptr); }

collection::~collection() { lxb_dom_collection_destroy(ptr, true); }

collection::element_iterator collection::begin() {
  return element_iterator(this, 0);
}

collection::element_iterator collection::end() {
  return element_iterator(this, this->length());
}

collection::element_iterator &collection::element_iterator::operator++() {
  idx++;
  return *this;
}

collection::element_iterator &collection::element_iterator::operator--() {
  idx--;
  return *this;
}

collection::element_iterator collection::element_iterator::operator++(int) {
  element_iterator retval = *this;
  ++(*this);
  return retval;
}

bool collection::element_iterator::operator==(element_iterator other) const {
  return idx == other.idx;
}

bool collection::element_iterator::operator!=(element_iterator other) const {
  return !(*this == other);
}

const element &collection::element_iterator::operator*() const {
  val = lxb_dom_collection_element(col->ptr, idx);
  static_assert(sizeof(lexbor::element) == sizeof(val) &&
                    alignof(lexbor::element) == alignof(decltype(val)),
                "Lexbor element must be convertible to a element pointer!");
  return reinterpret_cast<const element &>(val);
}

} // namespace lexbor
