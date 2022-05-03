#pragma once
#include <cstddef>
#include <lexbor/core/base.h>
#include <lexbor/core/types.h>
#include <string_view>

template <typename T, size_t N> size_t ARR_LEN(const T (&arr)[N]) noexcept {
  return N;
}

namespace lexbor {

// inline const char *to_chars(const lxb_char_t *in) { return (char *)in; }
// inline const lxb_char_t *to_lxb_chars(const char *in) {
//  return (lxb_char_t *)in;
//}

class string_view : public std::basic_string_view<lxb_char_t> {
public:
  using basic_string_view::basic_string_view;
  string_view(const std::string_view str)
      : std::basic_string_view<lxb_char_t>(
            reinterpret_cast<const lxb_char_t *>(str.data()), str.size()) {}
  string_view(const char *str)
      : std::basic_string_view<lxb_char_t>(
            reinterpret_cast<const lxb_char_t *>(str)) {}

  friend std::ostream &operator<<(std::ostream &os, string_view const &s);

protected:
  const std::string_view std_string_view() const {
    return std::string_view(reinterpret_cast<const char *>(this->data()),
                            this->size());
  }
};

std::ostream &operator<<(std::ostream &os, string_view const &s);

void throw_on_bad(lxb_status_t status, const char *message);

} // namespace lexbor
