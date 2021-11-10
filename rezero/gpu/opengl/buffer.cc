// Created by Dong Zhong on 2021/10/28.

#include "rezero/gpu/buffer.h"

#include "rezero/base/logging.h"
#include "rezero/gpu/opengl/state_machine_gl.h"
#include "rezero/gpu/opengl/utils.h"

namespace rezero {
namespace gpu {

Buffer::Buffer(std::size_t size, BufferType type, BufferUsage usage)
    : size_(size), type_(type), usage_(usage) {
  glGenBuffers(1, &buffer_.buffer_name_);
  REZERO_DCHECK(buffer_.buffer_name_ > 0);

  buffer_.buffer_type_ = Utils::ToGLBufferType(type_);
  buffer_.buffer_usage_ = Utils::ToGLBufferUsage(usage_);
}

Buffer::~Buffer() {
  if (buffer_.buffer_name_ > 0) {
    glDeleteBuffers(1, &buffer_.buffer_name_);
    auto& state_machine = StateMachineGL::GetCurrent();
    state_machine.UnbindBuffer(buffer_.buffer_type_, buffer_.buffer_name_);
    buffer_.buffer_name_ = 0;
  }
}

void Buffer::UpdateData(std::size_t size, const void* data) {
  REZERO_CHECK(size != 0 && size <= size_);

  if (buffer_.buffer_name_ > 0) {
    auto& state_machine = StateMachineGL::GetCurrent();
    state_machine.BindBuffer(buffer_.buffer_type_, buffer_.buffer_name_);

    glBufferData(buffer_.buffer_type_,
                 static_cast<GLsizeiptr>(size),
                 static_cast<const GLvoid*>(data),
                 buffer_.buffer_usage_);

    CHECK_GL_ERROR_DEBUG();
    buffer_.allocated_size_ = size;
  }
}

void Buffer::UpdateSubData(std::size_t offset, std::size_t size, const void* data) {
  REZERO_DCHECK(buffer_.allocated_size_ > 0)
      << "UpdateData should be invoked before UpdateSubData.";
  REZERO_DCHECK(offset + size <= buffer_.allocated_size_)
      << "Buffer size overflow.";

  if (buffer_.buffer_name_ > 0) {
    auto& state_machine = StateMachineGL::GetCurrent();
    state_machine.BindBuffer(buffer_.buffer_type_, buffer_.buffer_name_);

    glBufferSubData(buffer_.buffer_type_,
                    static_cast<GLintptr>(offset),
                    static_cast<GLsizeiptr>(size),
                    static_cast<const GLvoid*>(data));

    CHECK_GL_ERROR_DEBUG();
  }
}

} // namespace gpu
} // namespace rezero
