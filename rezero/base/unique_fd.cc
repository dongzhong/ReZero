// Created by Dong Zhong on 2021/09/15.

#include "rezero/base/unique_fd.h"

namespace rezero {
namespace internal {

void UniqueFDTraits::Free(int fd) {
  close(fd);
}

} // namespace internal

} // namespace rezero