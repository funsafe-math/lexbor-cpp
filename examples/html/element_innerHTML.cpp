#include "document.h"

int main(int argc, const char *argv[]) {
  //  lxb_html_element_t *element;
  //  lxb_html_body_element_t *body;
  //  lxb_html_document_t *document;

  static const lexbor::string_view html = "<div><span>blah-blah-blah</div>";

  static const lexbor::string_view inner = "<ul><li>1<li>2<li>3</ul>";

  /* Parse */
  lexbor::document document(html);

  /* Print Incoming Data */
  //  PRINT("HTML:");
  //  PRINT("%s", (const char *)html);
  //  PRINT("\nTree after parse:");
  //  serialize(lxb_dom_interface_node(document));
  std::cout << "HTML:" << html << "\nTree after parse:";
  document.serialize();

  /* Get BODY element */
  //  body = lxb_html_document_body_element(document);
  auto body = document.body_element();

  //  PRINT("\nHTML for innerHTML:");
  //  PRINT("%s", (const char *)inner);
  std::cout << "\nHTML for innerHTML:" << inner;

  //  element =
  //  lxb_html_element_inner_html_set(lxb_html_interface_element(body),
  //                                            inner, inner_len);
  body.inner_html_set(inner);

  /* Print Result */
  //  PRINT("\nTree after innerHTML set:");
  //  serialize(lxb_dom_interface_node(document));
  std::cout << "\nTree after innerHTML set:";
  document.serialize();

  /* Destroy all */
  //  lxb_html_document_destroy(document);

  return 0;
}
