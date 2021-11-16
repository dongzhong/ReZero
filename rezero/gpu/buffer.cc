// Created by Dong Zhong on 2021/11/15.

#include "rezero/gpu/buffer.h"

#include "rezero/base/logging.h"

namespace rezero {
namespace gpu {

Buffer::Buffer(BufferType type, BufferUsage usage, std::size_t size)
    : type_(type), usage_(usage), size_(size) {
  REZERO_DCHECK(size > 0);
}

Buffer::~Buffer() = default;

} // namespace gpu
} // namespace rezero
