// Created by Dong Zhong on 2021/09/13.

#ifndef REZERO_BASE_SIZE_H_
#define REZERO_BASE_SIZE_H_

#include <cstddef>

namespace rezero {

template<typename T, std::size_t N>
constexpr std::size_t size(T (&array)[N]) {
  return N;
}

} // namespace rezero

#endif // REZERO_BASE_SIZE_H_