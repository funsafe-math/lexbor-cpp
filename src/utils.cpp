#include "utils.h"
#include <stdexcept>
namespace lexbor {

std::ostream &operator<<(std::ostream &os, string_view const &s) {
  return os << s.std_string_view();
}

void throw_on_bad(lxb_status_t status, const char *message) {
  if (status != LXB_STATUS_OK) {
    throw std::runtime_error(message);
  }
}

} // namespace lexbor
