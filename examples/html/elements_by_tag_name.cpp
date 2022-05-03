/*
 * Copyright (C) 2018 Alexander Borisov
 *
 * Author: Alexander Borisov <borisov@lexbor.com>
 */

#include "collection.h"
#include "document.h"

int main(int argc, const char *argv[]) {
  const lexbor::string_view html = "<div a=b><span></div><div x=z></div>";
  lexbor::document document(html);

  lexbor::collection collection(document, 128);

  document.body_element().elements_by_tag_name(collection, "div");

  std::cout << "HTML:";
  std::cout << html;
  std::cout << "\nFind all 'div' elements by tag name 'div'.";
  std::cout << "Elements found:";

  lexbor::collection copy(std::move(collection));
  for (auto e : copy) {
    e.serialize();
  }

  return 0;
}
