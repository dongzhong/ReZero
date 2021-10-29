// Created by Dong Zhong on 2021/10/29.

#include "rezero/gpu/opengl/state_machine_gl.h"

namespace rezero {
namespace gpu {

StateMachineGL::StateMachineGL() = default;

StateMachineGL::~StateMachineGL() = default;

void StateMachineGL::BindBuffer(GLenum buffer_type, GLuint buffer_name) {
  if (buffer_type == GL_ARRAY_BUFFER) {
    if (buffer_name != bound_array_buffer_) {
      glBindBuffer(GL_ARRAY_BUFFER, buffer_name);
      bound_array_buffer_ = buffer_name;
    }
  } else {
    if (buffer_name != bound_element_array_buffer_) {
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer_name);
      bound_element_array_buffer_ = buffer_name;
    }
  }
}

void StateMachineGL::UnbindBuffer(GLenum buffer_type, GLuint buffer_name) {
  if (buffer_type == GL_ARRAY_BUFFER) {
    if (buffer_name == bound_array_buffer_) {
      bound_array_buffer_ = 0;
    }
  } else {
    if (buffer_name == bound_element_array_buffer_) {
      bound_element_array_buffer_ = 0;
    }
  }
}

} // namespace gpu
} // namespace rezero
