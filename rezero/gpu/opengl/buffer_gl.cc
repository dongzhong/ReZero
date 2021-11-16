// Created by Dong Zhong on 2021/11/15.

#include "rezero/gpu/opengl/buffer_gl.h"

#include "rezero/base/logging.h"
#include "rezero/gpu/opengl/state_machine_gl.h"
#include "rezero/gpu/opengl/utils_gl.h"

namespace rezero {
namespace gpu {

BufferGL::BufferGL(BufferType type, BufferUsage usage, std::size_t size)
    : Buffer(type, usage, size),
      buffer_type_(UtilsGL::ToGLBufferType(type)),
      buffer_usage_(UtilsGL::ToGLBufferUsage(usage)) {
  glGenBuffers(1, &buffer_name_);
  REZERO_DCHECK(buffer_name_ > 0);
}

BufferGL::~BufferGL() {
  if (buffer_name_ > 0) {
    auto& state_machine = StateMachineGL::GetCurrent();
    state_machine.UnbindBuffer(buffer_type_, buffer_name_);
    glDeleteBuffers(1, &buffer_name_);
  }
}

void BufferGL::UpdateData(void* data, std::size_t size) {
  REZERO_DCHECK(size <= size_);
  auto& state_machine = StateMachineGL::GetCurrent();
  state_machine.BindBuffer(buffer_type_, buffer_name_);

  glBufferData(buffer_type_,
               static_cast<GLsizeiptr>(size),
               static_cast<const GLvoid*>(data),
               buffer_usage_);
  allocated_size_ = size;
}

void BufferGL::UdpateSubData(void* data, std::size_t offset, std::size_t size) {
  REZERO_DCHECK(allocated_size_ > 0);
  REZERO_DCHECK(size + offset <= allocated_size_);

  auto& state_machine = StateMachineGL::GetCurrent();
  state_machine.BindBuffer(buffer_type_, buffer_name_);
  glBufferSubData(buffer_type_,
                  static_cast<GLintptr>(offset),
                  static_cast<GLsizeiptr>(size),
                  static_cast<const GLvoid*>(data));
}

} // namespace gpu
} // namespace rezero
