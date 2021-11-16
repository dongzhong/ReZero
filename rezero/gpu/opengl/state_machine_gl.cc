// Created by Dong Zhong on 2021/11/15.

#include "rezero/gpu/opengl/state_machine_gl.h"

namespace rezero {
namespace gpu {

StateMachineGL::StateMachineGL() = default;

StateMachineGL::~StateMachineGL() = default;

void StateMachineGL::BindBuffer(GLenum target, GLuint buffer_name) {
  GLuint* bound_buffer = nullptr;
  switch (target) {
    case GL_ARRAY_BUFFER:
      bound_buffer = &bound_vertex_buffer_;
      break;
    case GL_ELEMENT_ARRAY_BUFFER:
      bound_buffer = &bound_index_buffer_;
      break;
    default:
      REZERO_DCHECK(false) << "Unknown OpenGL buffer target. " << target;
      break;
  }

  if (bound_buffer != nullptr && *bound_buffer != buffer_name) {
    *bound_buffer = buffer_name;
    glBindBuffer(target, *bound_buffer);
  }
}

void StateMachineGL::UnbindBuffer(GLenum target, GLuint buffer_name) {
  GLuint* bound_buffer = nullptr;
  switch (target) {
    case GL_ARRAY_BUFFER:
      bound_buffer = &bound_vertex_buffer_;
      break;
    case GL_ELEMENT_ARRAY_BUFFER:
      bound_buffer = &bound_index_buffer_;
      break;
    default:
      REZERO_DCHECK(false) << "Unknown OpenGL buffer target. " << target;
      break;
  }

  if (bound_buffer != nullptr && *bound_buffer == buffer_name) {
    *bound_buffer = 0;
    glBindBuffer(target, *bound_buffer);
  }
}

void StateMachineGL::UseProgram(GLuint program) {
  if (used_program_ != program) {
    used_program_ = program;
    glUseProgram(used_program_);
  }
}

void StateMachineGL::UnuseProgram(GLuint program) {
  if (used_program_ == program) {
    used_program_ = 0;
    glUseProgram(used_program_);
  }
}

} // namespace gpu
} // namespace rezero
