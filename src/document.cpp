#include "document.h"

namespace lexbor {

document::document() { create(); }

document::document(const string_view html) {
  create();
  parse(html);
}

document::document(document &&other) {
  if (this == &other)
    return;
  this->get_ptr() = other.get_ptr();
  other.get_ptr() = nullptr;
}

document::~document() { lxb_html_document_destroy(this->get_ptr()); }

void document::parse(const string_view html) {
  lxb_html_document_parse(get_ptr(), html.data(), html.size());
}

void document::parse_chunk_begin() {
  auto status = lxb_html_document_parse_chunk_begin(get_ptr());
  if (status != LXB_STATUS_OK) {
    throw std::runtime_error("Failed to begin parsing HTML by chunks");
  }
}

void document::parse_chunk(const string_view chunk) {
  auto status =
      lxb_html_document_parse_chunk(get_ptr(), chunk.data(), chunk.size());

  if (status != LXB_STATUS_OK) {
    throw std::runtime_error("Failed to parse HTML chunk");
  }
}

void document::parse_chunk_end() {
  auto status = lxb_html_document_parse_chunk_end(get_ptr());
  if (status != LXB_STATUS_OK) {
    throw std::runtime_error("Failed to parse HTML");
  }
}

const string_view document::title() {
  size_t str_len;
  auto title = lxb_html_document_title(get_ptr(), &str_len);
  if (title == nullptr) {
    return "";
  }
  return string_view{title, str_len};
}

const string_view document::title_raw() {

  size_t str_len;
  auto title = lxb_html_document_title_raw(get_ptr(), &str_len);
  if (title == nullptr) {
    return "";
  }
  return string_view{title, str_len};
}

void document::title_set(const string_view new_title) {
  auto status = lxb_html_document_title_set(get_ptr(), new_title.data(),
                                            new_title.size());
  if (status != LXB_STATUS_OK) {
    throw std::runtime_error("Failed to change HTML title");
  }
}

tags_hash document::document_tags() {
  return tags_hash(lxb_html_document_tags(get_ptr()));
}

lexbor::body_element document::body_element() {
  return lexbor::body_element(lxb_html_document_body_element(get_ptr()));
}

element document::create_element(const string_view local_name,
                                 void *reserved_for_opt) {
  return element(lxb_dom_document_create_element(
      &get_ptr()->dom_document, local_name.data(), local_name.size(),
      reserved_for_opt));
}

text_node document::create_text_node(const string_view data) {

  auto *text = lxb_dom_document_create_text_node(&get_ptr()->dom_document,
                                                 data.data(), data.size());
  if (text == nullptr) {
    throw std::runtime_error("Failed to create text node");
  }
  return text;
}

void document::create() {
  get_ptr() = lxb_html_document_create();
  if (get_ptr() == 0)
    throw std::runtime_error("Failed to create HTML Document");
}

} // namespace lexbor
