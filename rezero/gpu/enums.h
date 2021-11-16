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

enum class BufferType : uint32_t {
  kVertex,
  kIndex,
};

enum class BufferUsage : uint32_t {
  kStatic,
  kDynamic,
};

} // namespace gpu
} // namespace rezero

#endif // REZERO_GPU_ENUMS_H_
