// Created by Dong Zhong on 2021/11/12.

#ifndef REZERO_GPU_ENUMS_H_
#define REZERO_GPU_ENUMS_H_

#include <cstdint>

namespace rezero {
namespace gpu {

enum class RenderingApi : uint32_t {
  kDefault,
  kOpenGL,
};

} // namespace gpu
} // namespace rezero

#endif // REZERO_GPU_ENUMS_H_
