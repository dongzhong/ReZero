// Created by Dong Zhong on 2021/10/28.

#ifndef REZERO_GPU_TYPES_H_
#define REZERO_GPU_TYPES_H_

#include <stdint.h>

namespace rezero {
namespace gpu {

template <typename T>
struct ImplType {
  // using type = xxx
};

class Buffer;
class CommandBuffer;
class Program;
class RenderPipeline;
class Texture;

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

#endif // REZERO_GPU_TYPES_H_
