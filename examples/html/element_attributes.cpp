#include "attribute.h"
#include "collection.h"
#include "document.h"

int main(int argc, const char *argv[]) {

  static const lexbor::string_view html = "<div id=my-best-id></div>";

  const std::string_view name = "my-name";

  /* Parse */
  lexbor::document document(html);

  /* Print Incoming Data */
  std::cout << "HTML:" << html << '\n';
  std::cout << "Tree after parse:";
  document.serialize();

  /* Create Collection for elements */
  lexbor::collection collection(document);

  //  /* Get BODY element (root for search) */
  auto body = document.body_element();
  lexbor::element element = body;

  //  /* Find DIV eleemnt */
  element.elements_by_tag_name(collection, "div");

  if (collection.length() == 0) {
    throw std::runtime_error("Failed to find DIV element");
  }

  //  /* Append new attribute */
  element = collection.at(0);

  element.set_attribute(name, "oh God");

  //  /* Print Result */
  std::cout << "Tree after append attribute to DIV element: ";
  document.serialize();

  //  /* Check exist */
  auto is_exist = element.has_attribute(name);

  if (is_exist) {
    std::cout << "Element has attribute \"" << name << "\": true" << '\n';
  } else {
    std::cout << "Element has attribute \"" << name << ": false" << '\n';
  }

  //  /* Get value by qualified name */
  auto value = element.get_attribute(name);

  std::cout << "Get attribute value by qualified name \"" << name
            << "\": " << value << '\n';

  //  /* Iterator */
  std::cout << "Get element attributes by iterator:\n";

  for (auto attr : element) {
    auto tmp = attr.qualified_name();
    std::cout << "Name: " << tmp;
    tmp = attr.value();
    std::cout << (tmp.empty() ? "" : "; Value: ") << tmp << '\n';
  }

  //  /* Change value */
  std::cout << "\nChange attribute value:" << '\n';
  std::cout << "Element before attribure \"" << name << "\" change:";
  element.serialize();

  auto attr = element.attr_by_name(name);
  attr.set_value("new value");

  std::cout << "Element after attribute \"" << name << "\" change: " << '\n';
  element.serialize();

  //  /* Remove new attribute by name */
  element.remove_attribute(name);

  //  /* Print Result */
  std::cout << "\nTree after remove attribute form DIV element:";
  document.serialize();
  return 0;
}
