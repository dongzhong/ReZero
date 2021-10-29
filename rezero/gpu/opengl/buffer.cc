// Created by Dong Zhong on 2021/10/28.

#include "rezero/gpu/buffer.h"

#include "rezero/base/logging.h"

namespace rezero {
namespace gpu {

Buffer::Buffer() {
  glGenBuffers(1, &buffer_.buffer_name_);
  REZERO_DCHECK(buffer_.buffer_name_ > 0);
}

Buffer::~Buffer() {
  if (buffer_.buffer_name_ > 0) {
    glDeleteBuffers(1, &buffer_.buffer_name_);
    buffer_.buffer_name_ = 0;
  }
}

} // namespace gpu
} // namespace rezero
