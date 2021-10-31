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

void StateMachineGL::BindTexture(int unit, GLenum texture_type, GLuint texture_name) {
  if (active_texture_unit_ != unit) {
    glActiveTexture(GL_TEXTURE0 + unit);
    active_texture_unit_ = unit;
  }

  if (bound_textures_[active_texture_unit_][texture_type] != texture_name) {
    glBindTexture(texture_type, texture_name);
    bound_textures_[active_texture_unit_][texture_type] = texture_name;
  }
}

void StateMachineGL::UnbindTexture(int unit, GLenum texture_type, GLuint texture_name) {
  if (bound_textures_[unit][texture_type] != texture_name) {
    return;
  }

  if (active_texture_unit_ != unit) {
    glActiveTexture(GL_TEXTURE0 + unit);
    active_texture_unit_ = unit;
  }

  glBindTexture(texture_type, 0);
  bound_textures_[active_texture_unit_][texture_type] = 0;
}

void StateMachineGL::UnbindTextureForAllUnit(GLenum texture_type, GLuint texture_name) {
  for (int i = 0; i < kMaxTextureUnits; ++i) {
    if (bound_textures_[i][texture_type] == texture_name) {
      if (active_texture_unit_ != i) {
        glActiveTexture(GL_TEXTURE0 + i);
        active_texture_unit_ = i;
      }

      glBindTexture(texture_type, 0);
      bound_textures_[i][texture_type] = 0;
    }
  }
}

} // namespace gpu
} // namespace rezero
