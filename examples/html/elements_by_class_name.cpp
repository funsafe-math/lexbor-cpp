/*
 * Copyright (C) 2018 Alexander Borisov
 *
 * Author: Alexander Borisov <borisov@lexbor.com>
 */

#include "collection.h"
#include "document.h"

int main(int argc, const char *argv[]) {
  const lexbor::string_view html = "<div class=\"best blue some\"><span></div>"
                                   "<div class=\"red pref_best grep\"></div>"
                                   "<div class=\"red best grep\"></div>"
                                   "<div class=\"red c++ best\"></div>";

  lexbor::document document(html);

  lexbor::collection collection(document);

  document.body_element().elements_by_class_name(collection, "best");

  std::cout << "HTML:";
  std::cout << html;
  std::cout << "\nFind all 'div' elements by class name 'best'.";
  std::cout << "Elements found:";

  for (auto e : collection) {
    e.serialize();
  }

  return 0;
}
