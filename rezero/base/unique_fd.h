// Created by Dong Zhong on 2021/09/15.

#ifndef REZERO_BASE_UNIQUE_FD_H_
#define REZERO_BASE_UNIQUE_FD_H_

#include "rezero/base/unique_object.h"

#include <dirent.h>
#include <unistd.h>

namespace rezero {
namespace internal {

struct UniqueFDTraits {
  static int InvalidValue() { return -1; }
  static bool IsValid(int value) { return value >= 0; }
  static void Free(int fd);
};

} // namespace internal

using UniqueFD = UniqueObject<int, internal::UniqueFDTraits>;

} // namespace rezero

#endif // REZERO_BASE_UNIQUE_FD_H_