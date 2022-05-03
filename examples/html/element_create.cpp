#include "document.h"
#include "tag.h"

int main(int argc, const char *argv[]) {
  //  /* Parse */
  lexbor::document document("");

  auto body = document.body_element();

  //  /* Print Current Tree */
  std::cout << "Inital HTML Tree:";
  document.serialize();
  std::cout << '\n';

  //  /* Create all known tags */
  auto tags = document.document_tags();

  for (lexbor::tag tag_id = LXB_TAG_A; tag_id < LXB_TAG__LAST_ENTRY; tag_id++) {
    auto tag_name = tags.name_by_id(tag_id);
    auto element = document.create_element(tag_name);

    //    /*
    //     * If the tag is void then we do not create a text node.
    //     * See
    //     https://html.spec.whatwg.org/multipage/syntax.html#void-elements
    //     */

    if (tag_id.is_void()) {
      std::cout << "Create element by tag name \"" << tag_name << "\": ";
    } else {
      std::cout << "Create element by tag name \"" << tag_name
                << "\" and append text node: ";

      auto text = document.create_text_node(tag_name);

      element.insert_child(text);
    }
    element.serialize();

    body.insert_child(element);
  }

  //  /* Print Result */
  std::cout << "\nTree after create elements:";
  document.serialize();


  return 0;
}
