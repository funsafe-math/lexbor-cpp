#include "document.h"

int main(int argc, const char *argv[]) {
  //  lxb_status_t status;
  //  lxb_html_document_t *document;

  static const std::string_view html[64] = {
      "<!DOCT",      "YPE htm",       "l>",           "<html><head>",
      "<ti",         "tle>HTML chun", "ks parsing</", "title>",
      "</head><bod", "y><div cla",    "ss=",          "\"bestof",
      "class",       "\">",           "good for me",  "</div>",
      "\0"};

  /* Initialization */
  //  document = lxb_html_document_create();
  //  if (document == NULL) {
  //    FAILED("Failed to create HTML Document");
  //  }
  lexbor::document document;

  /* Parse HTML */
  //  status = lxb_html_document_parse_chunk_begin(document);
  //  if (status != LXB_STATUS_OK) {
  //    FAILED("Failed to parse HTML");
  //  }
  document.parse_chunk_begin();

  //  PRINT("Incoming HTML chunks:");
  std::cout << "Incoming HTML chunks";

  for (size_t i = 0; html[i][0] != '\0'; i++) {
    //    PRINT("%s", (const char *)html[i]);
    std::cout << html[i] << '\n';

    //    status = lxb_html_document_parse_chunk(document, html[i],
    //                                           strlen((const char *)html[i]));

    //    if (status != LXB_STATUS_OK) {
    //      FAILED("Failed to parse HTML chunk");
    //    }
    document.parse_chunk(html[i]);
  }

  //  status = lxb_html_document_parse_chunk_end(document);
  //  if (status != LXB_STATUS_OK) {
  //    FAILED("Failed to parse HTML");
  //  }
  document.parse_chunk_end();

  /* Print Result */
  //  PRINT("\nHTML Tree:");
  //  serialize(lxb_dom_interface_node(document));
  document.serialize();

  /* Destroy document */
  //  lxb_html_document_destroy(document);

  return 0;
}
