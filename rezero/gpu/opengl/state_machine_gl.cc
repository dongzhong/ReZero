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

void StateMachineGL::ActiveTextureUnit(int unit) {
  REZERO_DCHECK(unit >= 0 && unit < kMaxTextureUnits);
  if (active_texture_unit_ != unit) {
    active_texture_unit_ = unit;
    glActiveTexture(GL_TEXTURE0 + active_texture_unit_);
  }
}

void StateMachineGL::BindTexture(int unit, GLenum target, GLuint texture) {
  REZERO_DCHECK(unit >= 0 && unit < kMaxTextureUnits);
  if (bound_textures_[unit][target] != texture) {
    ActiveTextureUnit(unit);
    bound_textures_[unit][target] = texture;
    glBindTexture(target, texture);
  }
}

void StateMachineGL::UnbindTexture(GLenum target, GLuint texture) {
  if (texture == 0) {
    return;
  }
  for (int i = 0; i < kMaxTextureUnits; ++i) {
    if (bound_textures_[i][target] == texture) {
      ActiveTextureUnit(i);
      bound_textures_[i][target] = 0;
      glBindTexture(target, 0);
    }
  }
}

void StateMachineGL::UnbindTextureAtUnit(int unit, GLenum target, GLuint texture) {
  REZERO_DCHECK(unit >= 0 && unit < kMaxTextureUnits);
  if (texture == 0) {
    return;
  }
  if (bound_textures_[unit][target] == texture) {
    ActiveTextureUnit(unit);
    bound_textures_[unit][target] = 0;
    glBindTexture(target, 0);
  }
}

} // namespace gpu
} // namespace rezero
