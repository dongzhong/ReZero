// Created by Dong Zhong on 2021/11/03.

#ifndef REZERO_GPU_OPENGL_TRAITS_TRAIT_RENDER_PASS_H_
#define REZERO_GPU_OPENGL_TRAITS_TRAIT_RENDER_PASS_H_

#include "rezero/gpu/opengl/includes.h"
#include "rezero/gpu/render_pass_descriptor.h"
#include "rezero/gpu/types.h"

namespace rezero {
namespace gpu {

namespace opengl {

using EndRenderPassCallback = std::function<void(std::size_t)>;

class RenderPassGL {
 public:
  RenderPassGL();
  ~RenderPassGL();

  void SetRenderPassId(std::size_t id);

  void SetEndRenderPassCallback(const EndRenderPassCallback& callback);

  std::size_t GetRenderPassId() const { return render_pass_id_; }

  void EndRenderPass();

  void PerformDrawing();

  // Update attributes
  void SetRenderPassDescriptor(const RenderPassDescriptor& descriptor);

  void SetVertexBuffer(const std::shared_ptr<Buffer>& vertex_buffer);

  void SetIndexBuffer(const std::shared_ptr<Buffer>& index_buffer);

  void SetDepthStencil(const DepthStencilDescriptor& descriptor);

  void SetReferenceValue(unsigned int value);

  void SetReferenceValue(unsigned int front_value, unsigned int back_value);

 private:
  void PrepareDrawing();

  void PrepareRenderPassDescriptor();

  void PrepareBuffers();

  void PrepareDepthStencil();

  void AfterDraw();

  std::size_t render_pass_id_ = 0;
  EndRenderPassCallback callback_ = {};

  RenderPassDescriptor render_pass_descriptor_;

  GLuint origin_framebuffer_ = 0;
  GLuint curren_framebuffer_ = 0;

  std::shared_ptr<Buffer> vertex_buffer_ = nullptr;
  std::shared_ptr<Buffer> index_buffer_ = nullptr;

  // Depth and Stencil
  bool enable_depth_test_ = false;
  bool enable_stencil_test_ = false;

  GLenum depth_compare_function_ = GL_LESS;
  bool depth_write_enable_ = true;

  GLenum front_stencil_compare_function_ = GL_ALWAYS;
  GLenum front_stencil_failed_operation_ = GL_KEEP;
  GLenum front_depth_failed_operation_ = GL_KEEP;
  GLenum front_test_pass_operation_ = GL_KEEP;
  unsigned int front_stencil_read_mask_ = -1;
  unsigned int front_stencil_write_mask_ = -1;
  unsigned int front_reference_value_ = 0;

  GLenum back_stencil_compare_function_ = GL_ALWAYS;
  GLenum back_stencil_failed_operation_ = GL_KEEP;
  GLenum back_depth_failed_operation_ = GL_KEEP;
  GLenum back_test_pass_operation_ = GL_KEEP;
  unsigned int back_stencil_read_mask_ = -1;
  unsigned int back_stencil_write_mask_ = -1;
  unsigned int back_reference_value_ = 0;

  REZERO_DISALLOW_COPY_AND_ASSIGN(RenderPassGL);
};

} // namespace opengl

template <>
struct ImplType<RenderPass> {
  using type = opengl::RenderPassGL;
};

} // namespace gpu
} // namespace rezero

#endif // REZERO_GPU_OPENGL_TRAITS_TRAIT_RENDER_PASS_H_
