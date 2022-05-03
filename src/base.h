#pragma once
#include <type_traits>
#include <utility>

namespace lexbor {

class base {
private:
  void *ptr = nullptr;

protected:
  template <class LXB_T> LXB_T *&get_ptr_impl() {
    return reinterpret_cast<LXB_T *&>(ptr);
  }

  template <class LXB_T> LXB_T *const &get_ptr_impl() const {
    return reinterpret_cast<LXB_T *const &>(ptr);
  }
};

} // namespace lexbor
