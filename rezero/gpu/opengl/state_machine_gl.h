// Created by Dong Zhong on 2021/10/29.

#ifndef REZERO_GPU_OPENGL_STATE_MACHINE_GL_H_
#define REZERO_GPU_OPENGL_STATE_MACHINE_GL_H_

#include <array>
#include <unordered_map>
#include <unordered_set>
#include <utility>

#include "rezero/base/thread_singleton.h"
#include "rezero/gpu/opengl/includes.h"
#include "rezero/gpu/opengl/utils.h"
#include "rezero/gpu/vertex_layout.h"

namespace rezero {
namespace gpu {

class StateMachineGL : public ThreadSingleton<StateMachineGL> {
 public:
  StateMachineGL();
  ~StateMachineGL();

  GLuint GetCurrentBoundFramebuffer();

  void SetClearColorValue(const std::array<float, 4>& color_value);
  void SetClearDepthValue(float depth_value);
  void SetClearStencilValue(float stencil_value);

  void BindBuffer(GLenum buffer_type, GLuint buffer_name);
  void UnbindBuffer(GLenum buffer_type, GLuint buffer_name);

  void BindTexture(int unit, GLenum texture_type, GLuint texture_name);
  void UnbindTexture(int unit, GLenum texture_type, GLuint texture_name);
  void UnbindTextureForAllUnit(GLenum texture_type, GLuint texture_name);

  void UseProgram(GLuint program);
  void UnuseProgram(GLuint program);

  void SetUniform(bool is_array, GLenum type, GLuint location, GLsizei count, void* data);
  void SetUniformTexture(GLuint location, GLuint slot);

  void UpdateVertexAttributes(
      const std::unordered_map<std::string, VertexLayout::Attribute>& attributes,
      std::size_t stride);

  void SetBlendEnable(bool enabled);

  void SetBlendEquation(GLenum rgb_operation, GLenum alpha_operation);
  void SetBlendFunc(GLenum src_rgb_factor,
                    GLenum src_alpha_factor,
                    GLenum dst_rgb_factor,
                    GLenum dst_alpha_factor);

  void SetDepthTest(bool enabled);
  void SetStencilTest(bool enabled);

  void SetDepthCompareFunction(GLenum compare_function);
  void SetDepthWriteMask(bool mask);

  void SetFrontStencilFunction(GLenum function, GLint reference_value, GLuint mask);

  void SetBackStencilFunction(GLenum function, GLint reference_value, GLuint mask);

  void SetFrontStencilOperation(GLenum stencil_failed,
                                GLenum depth_failed,
                                GLenum pass);
  void SetBackStencilOperation(GLenum stencil_failed,
                               GLenum depth_failed,
                               GLenum pass);

  void SetFrontStencilMask(GLuint mask);
  void SetBackStencilMask(GLuint mask);

  void SetBlendColor(float r, float g, float b, float a);

  void SetViewport(int x, int y, unsigned int width, unsigned int height);

  void SetScissorEnable(bool enable);
  void SetScissor(int x, int y, unsigned int width, unsigned int height);

  void SetCullMode(bool enable, GLenum mode);

  void SetWindingMode(GLenum mode);

 private:
  std::array<float, 4> clear_color_value_ = { { 0.0f, 0.0f, 0.0f, 0.0f } };
  float clear_depth_value_ = 1.0f;
  float clear_stencil_value_ = 0.0f;

  GLuint bound_array_buffer_ = 0;
  GLuint bound_element_array_buffer_ = 0;

  // key: texture slot
  unsigned int active_texture_unit_ = 0;
  std::array<std::unordered_map<GLenum, GLuint>, kMaxTextureUnits> bound_textures_ = {};

  GLuint used_program_ = 0;

  std::unordered_set<GLuint> enabled_attribs_;

  // Blend
  bool enable_blend_ = false;
  GLenum alpha_blend_operation_ = GL_FUNC_ADD;
  GLenum rgb_blend_operation_ = GL_FUNC_ADD;

  GLenum src_alpha_blend_factor_ = GL_ONE;
  GLenum src_rgb_blend_factor_ = GL_ONE;
  GLenum dst_alpha_blend_factor_ = GL_ZERO;
  GLenum dst_rgb_blend_factor_ = GL_ZERO;

  bool color_mask_red_ = true;
  bool color_mask_green_ = true;
  bool color_mask_blue_ = true;
  bool color_mask_alpha_ = true;

  // Depth and stencil
  bool enable_depth_test_ = false;
  bool enable_stencil_test = false;

  GLenum depth_compare_function_ = GL_LESS;
  bool depth_write_enable_ = true;

  GLenum front_stencil_compare_function_ = GL_ALWAYS;
  GLenum front_stencil_failed_operation_ = GL_KEEP;
  GLenum front_depth_failed_operation_ = GL_KEEP;
  GLenum front_test_pass_operation_ = GL_KEEP;
  unsigned int front_stencil_read_mask_ = -1;
  unsigned int front_stencil_write_mask_ = -1;
  unsigned int front_stencil_reference_value_ = 0;

  GLenum back_stencil_compare_function_ = GL_ALWAYS;
  GLenum back_stencil_failed_operation_ = GL_KEEP;
  GLenum back_depth_failed_operation_ = GL_KEEP;
  GLenum back_test_pass_operation_ = GL_KEEP;
  unsigned int back_stencil_read_mask_ = -1;
  unsigned int back_stencil_write_mask_ = -1;
  unsigned int back_stencil_reference_value_ = 0;

  float blend_color_red_ = 0.0f;
  float blend_color_green_ = 0.0f;
  float blend_color_blue_ = 0.0f;
  float blend_color_alpha_ = 0.0f;

  Region viewport_;

  bool scissor_enabled_ = false;
  Region scissor_;

  bool enable_cull_face_ = false;
  GLenum cull_mode_ = GL_BACK;

  GLenum winding_mode_ = GL_CCW;

  REZERO_DISALLOW_COPY_AND_ASSIGN(StateMachineGL);
};

} // namespace gpu
} // namespace rezero

#endif // REZERO_GPU_OPENGL_STATE_MACHINE_GL_H_
