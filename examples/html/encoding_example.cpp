/*
 * Copyright (C) 2019 Alexander Borisov
 *
 * Author: Alexander Borisov <borisov@lexbor.com>
 */

#include "encoding.h"
#include <fstream>
#include <iostream>

static void usage(void) {
  printf("Usage:\n");
  printf("    encoding <file-path-to-html>\n");
}

int main(int argc, const char *argv[]) {
  if (argc != 2) {
    usage();
    exit(EXIT_SUCCESS);
  }

  std::fstream file(argv[1]);
  if (!file.is_open())
    std::cerr << "Failed to open file " << argv[1] << '\n';
  std::string html((std::istreambuf_iterator<char>(file)),
                   (std::istreambuf_iterator<char>()));
  file.close();

  lexbor::encoding encoding;
  lexbor::string_view html_sv(html);

  /*
   * By specification:
   * "For instance, a user agent might wait 500ms or 1024 bytes,
   *  whichever came first."
   *
   * This is not a strict rule, but it saves time. Most often,
   * a meta encoding tag is present in the first 1024 bytes of HTML.
   */

  /*
     if (len > 1024) {
         len = 1024;
     }
 */

  encoding.determine(html_sv);

  auto entry = encoding.meta_entry(0);
  if (entry.empty())
    std::cout << "Encoding not found\n";
  std::cout << entry << '\n';

  return 0;
}
