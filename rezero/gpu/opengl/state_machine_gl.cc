// Created by Dong Zhong on 2021/10/29.

#include "rezero/gpu/opengl/state_machine_gl.h"

namespace rezero {
namespace gpu {

StateMachineGL::StateMachineGL() = default;

StateMachineGL::~StateMachineGL() = default;

GLuint StateMachineGL::GetCurrentBoundFramebuffer() {
  GLint bound_frame_buffer = 0;
  glGetIntegerv(GL_FRAMEBUFFER_BINDING, &bound_frame_buffer);
  return bound_frame_buffer;
}

void StateMachineGL::SetClearColorValue(const std::array<float, 4>& color_value) {
  if (clear_color_value_ != color_value) {
    clear_color_value_ = color_value;
    glClearColor(clear_color_value_[0],
                 clear_color_value_[1],
                 clear_color_value_[2],
                 clear_color_value_[3]);
  }
}

void StateMachineGL::SetClearDepthValue(float depth_value) {
  if (clear_depth_value_ != depth_value) {
    clear_depth_value_ = depth_value;
    glClearDepthf(clear_depth_value_);
  }
}

void StateMachineGL::SetClearStencilValue(float stencil_value) {
  if (clear_stencil_value_ != stencil_value) {
    clear_stencil_value_ = stencil_value;
    glClearStencil(clear_stencil_value_);
  }
}

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

void StateMachineGL::UseProgram(GLuint program) {
  if (used_program_ != program) {
    glUseProgram(program);
    used_program_ = program;
  }
}

void StateMachineGL::UnuseProgram(GLuint program) {
  if (used_program_ == program) {
    glUseProgram(0);
    used_program_ = 0;
  }
}

void StateMachineGL::UpdateVertexAttributes(
    const std::unordered_map<std::string, VertexLayout::Attribute>& attributes,
    std::size_t stride) {
  std::unordered_set<GLuint> enabled_attribs;
  for (auto&& [name, attribute] : attributes) {
    if (attribute.index < 0) {
      continue;
    }
    enabled_attribs.insert(attribute.index);
    glEnableVertexAttribArray(static_cast<GLuint>(attribute.index));
    glVertexAttribPointer(static_cast<GLuint>(attribute.index),
                          Utils::GetAttributeSize(attribute.format),
                          Utils::ToGLAttributeType(attribute.format),
                          attribute.need_normalize,
                          static_cast<GLsizei>(stride),
                          reinterpret_cast<const GLvoid*>(attribute.offset));
  }

  for (auto index = enabled_attribs_.begin();
       index != enabled_attribs_.end();) {
     if (enabled_attribs.count(*index) == 0) {
       glDisableVertexAttribArray(*index);
       index = enabled_attribs_.erase(index);
     }
  }
}

void StateMachineGL::SetBlendEnable(bool enabled) {
  if (enable_blend_ != enabled) {
    enable_blend_ = enabled;
    if (enable_blend_) {
      glEnable(GL_BLEND);
    } else {
      glDisable(GL_BLEND);
    }
  }
}

void StateMachineGL::SetBlendEquation(GLenum rgb_operation, GLenum alpha_operation) {
  if (rgb_blend_operation_ != rgb_operation ||
      alpha_blend_operation_ != alpha_operation) {
    rgb_blend_operation_ = rgb_operation;
    alpha_blend_operation_ = alpha_operation;
    if (rgb_blend_operation_ == alpha_blend_operation_) {
      glBlendEquation(rgb_blend_operation_);
    } else {
      glBlendEquationSeparate(rgb_blend_operation_, alpha_blend_operation_);
    }
  }
}

void StateMachineGL::SetBlendFunc(GLenum src_rgb_factor,
                                  GLenum src_alpha_factor,
                                  GLenum dst_rgb_factor,
                                  GLenum dst_alpha_factor) {
  if (src_rgb_blend_factor_ != src_rgb_factor ||
      src_alpha_blend_factor_ != src_alpha_factor ||
      dst_rgb_blend_factor_ != dst_rgb_factor ||
      dst_alpha_blend_factor_ != dst_alpha_factor) {
    src_rgb_blend_factor_ = src_rgb_factor;
    src_alpha_blend_factor_ = src_alpha_factor;
    dst_rgb_blend_factor_ = dst_rgb_factor;
    dst_alpha_blend_factor_ = dst_alpha_factor;
    if (src_rgb_blend_factor_ == src_alpha_blend_factor_ &&
        dst_rgb_blend_factor_ == dst_alpha_blend_factor_) {
      glBlendFunc(src_rgb_blend_factor_, dst_rgb_blend_factor_);
    } else {
      glBlendFuncSeparate(src_rgb_blend_factor_,
                          dst_rgb_blend_factor_,
                          src_alpha_blend_factor_,
                          dst_alpha_blend_factor_);
    }
  }
}

void StateMachineGL::SetDepthTest(bool enabled) {
  if (enable_depth_test_ != enabled) {
    enable_depth_test_ = enabled;
    if (enable_depth_test_) {
      glEnable(GL_DEPTH_TEST);
    } else {
      glDisable(GL_DEPTH_TEST);
    }
  }
}

void StateMachineGL::SetStencilTest(bool enabled) {
  if (enable_stencil_test != enabled) {
    enable_stencil_test = enabled;
    if (enable_stencil_test) {
      glEnable(GL_STENCIL_TEST);
    } else {
      glDisable(GL_STENCIL_TEST);
    }
  }
}

void StateMachineGL::SetDepthCompareFunction(GLenum compare_function) {
  if (depth_compare_function_ != compare_function) {
    depth_compare_function_ = compare_function;
    glDepthFunc(depth_compare_function_);
  }
}

void StateMachineGL::SetDepthWriteMask(bool mask) {
  if (depth_write_enable_ != mask) {
    depth_write_enable_ = mask;
    glDepthMask(static_cast<GLboolean>(depth_write_enable_));
  }
}

void StateMachineGL::SetFrontStencilFunction(GLenum function,
                                             GLint reference_value,
                                             GLuint mask) {
  if (front_stencil_compare_function_ != function ||
      front_stencil_reference_value_ != reference_value ||
      front_stencil_read_mask_ != mask) {
    front_stencil_compare_function_ = function;
    front_stencil_reference_value_ = reference_value;
    front_stencil_read_mask_ = mask;
    glStencilFuncSeparate(GL_FRONT,
                          front_stencil_compare_function_,
                          front_stencil_reference_value_,
                          front_stencil_read_mask_);
  }
}

void StateMachineGL::SetBackStencilFunction(GLenum function,
                                            GLint reference_value,
                                            GLuint mask) {
  if (back_stencil_compare_function_ != function ||
      back_stencil_reference_value_ != reference_value ||
      back_stencil_read_mask_ != mask) {
    back_stencil_compare_function_ = function;
    back_stencil_reference_value_ = reference_value;
    back_stencil_read_mask_ = mask;
    glStencilFuncSeparate(GL_FRONT,
                          back_stencil_compare_function_,
                          back_stencil_reference_value_,
                          back_stencil_read_mask_);
  }
}

void StateMachineGL::SetFrontStencilOperation(GLenum stencil_failed,
                                              GLenum depth_failed,
                                              GLenum pass) {
  if (front_stencil_failed_operation_ != stencil_failed ||
      front_depth_failed_operation_ != depth_failed ||
      front_test_pass_operation_ != pass) {
    front_stencil_failed_operation_ = stencil_failed;
    front_depth_failed_operation_ = depth_failed;
    front_test_pass_operation_ = pass;
    glStencilOpSeparate(GL_FRONT,
                        front_stencil_failed_operation_,
                        front_depth_failed_operation_,
                        front_test_pass_operation_);
  }
}

void StateMachineGL::SetBackStencilOperation(GLenum stencil_failed,
                                             GLenum depth_failed,
                                             GLenum pass) {
  if (back_stencil_failed_operation_ != stencil_failed ||
      back_depth_failed_operation_ != depth_failed ||
      back_test_pass_operation_ != pass) {
    back_stencil_failed_operation_ = stencil_failed;
    back_depth_failed_operation_ = depth_failed;
    back_test_pass_operation_ = pass;
    glStencilOpSeparate(GL_BACK,
                        back_stencil_failed_operation_,
                        back_depth_failed_operation_,
                        back_test_pass_operation_);
  }
}

void StateMachineGL::SetFrontStencilMask(GLuint mask) {
  if (front_stencil_write_mask_ != mask) {
    front_stencil_write_mask_ = mask;
    glStencilMaskSeparate(GL_FRONT, front_stencil_write_mask_);
  }
}

void StateMachineGL::SetBackStencilMask(GLuint mask) {
  if (back_stencil_write_mask_ != mask) {
    back_stencil_write_mask_ = mask;
    glStencilMaskSeparate(GL_BACK, back_stencil_write_mask_);
  }
}

void StateMachineGL::SetBlendColor(float r, float g, float b, float a) {
  if (blend_color_red_ != r ||
      blend_color_green_ != g ||
      blend_color_blue_ != b ||
      blend_color_alpha_ != a) {
    blend_color_red_ = r;
    blend_color_green_ = g;
    blend_color_blue_ = b;
    blend_color_alpha_ = a;
    glBlendColor(static_cast<GLfloat>(blend_color_red_),
                 static_cast<GLfloat>(blend_color_green_),
                 static_cast<GLfloat>(blend_color_blue_),
                 static_cast<GLfloat>(blend_color_alpha_));
  }
}

void StateMachineGL::SetViewport(int x,
                                 int y,
                                 unsigned int width,
                                 unsigned int height) {
  Region viewport { x, y, width, height };
  if (viewport_ != viewport) {
    viewport_ = viewport;
    glViewport(static_cast<GLint>(viewport_.x),
               static_cast<GLint>(viewport_.y),
               static_cast<GLsizei>(viewport_.width),
               static_cast<GLsizei>(viewport_.height));
  }
}

void StateMachineGL::SetScissor(int x,
                                int y,
                                unsigned int width,
                                unsigned int height) {
  Region scissor { x, y, width, height };
  if (scissor_ != scissor) {
    scissor_ = scissor;
    glScissor(static_cast<GLint>(scissor_.x),
              static_cast<GLint>(scissor_.y),
              static_cast<GLsizei>(scissor_.width),
              static_cast<GLsizei>(scissor_.height));
  }
}

void StateMachineGL::SetCullMode(bool enable, GLenum mode) {
  if (enable_cull_face_ != enable) {
    enable_cull_face_ = enable;
    if (enable_cull_face_) {
      glEnable(GL_CULL_FACE);
    } else {
      glDisable(GL_CULL_FACE);
    }
  }

  if (enable_cull_face_ && cull_mode_ != mode) {
    cull_mode_ = mode;
    glCullFace(cull_mode_);
  }
}

void StateMachineGL::SetWindingMode(GLenum mode) {
  if (winding_mode_ != mode) {
    winding_mode_ = mode;
    glFrontFace(winding_mode_);
  }
}

} // namespace gpu
} // namespace rezero
