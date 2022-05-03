#include "exception.h"
#include "utils.h"
#include <stdexcept>

#define ADD_ROW(x) [x] = #x

namespace {
const char *lexbor_enum_names[] = {
    ADD_ROW(LXB_STATUS_OK),
    ADD_ROW(LXB_STATUS_ERROR),
    ADD_ROW(LXB_STATUS_ERROR_MEMORY_ALLOCATION),
    ADD_ROW(LXB_STATUS_ERROR_OBJECT_IS_NULL),
    ADD_ROW(LXB_STATUS_ERROR_SMALL_BUFFER),
    ADD_ROW(LXB_STATUS_ERROR_INCOMPLETE_OBJECT),
    ADD_ROW(LXB_STATUS_ERROR_NO_FREE_SLOT),
    ADD_ROW(LXB_STATUS_ERROR_TOO_SMALL_SIZE),
    ADD_ROW(LXB_STATUS_ERROR_NOT_EXISTS),
    ADD_ROW(LXB_STATUS_ERROR_WRONG_ARGS),
    ADD_ROW(LXB_STATUS_ERROR_WRONG_STAGE),
    ADD_ROW(LXB_STATUS_ERROR_UNEXPECTED_RESULT),
    ADD_ROW(LXB_STATUS_ERROR_UNEXPECTED_DATA),
    ADD_ROW(LXB_STATUS_ERROR_OVERFLOW),
    ADD_ROW(LXB_STATUS_CONTINUE),
    ADD_ROW(LXB_STATUS_SMALL_BUFFER),
    ADD_ROW(LXB_STATUS_ABORTED),
    ADD_ROW(LXB_STATUS_STOPPED),
    ADD_ROW(LXB_STATUS_NEXT),
    ADD_ROW(LXB_STATUS_STOP),
};
}
#undef ADD_ROW

lexbor::exception::exception(const lxb_status_t _code) {
  if (_code == LXB_STATUS_OK)
    throw std::runtime_error(
        "Cannot create an exception if no error happened!");
  if (_code > ARR_LEN(lexbor_enum_names))
    throw std::runtime_error("Unknown error code, if you think this is a bug, "
                             "please contact maintainer");
  this->code = static_cast<decltype(this->code)>(_code);
}

const char *lexbor::exception::what() {
  return lexbor_enum_names[this->code];
}
