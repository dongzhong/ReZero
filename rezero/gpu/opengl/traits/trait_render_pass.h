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

enum class DrawMethod : uint32_t {
  kArrays,
  kElements,
};

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

  void SetProgramState(const std::shared_ptr<ProgramState>& program_state);

  void SetBlendDescriptor(const BlendDescriptor& descriptor);

  void SetVertexBuffer(const std::shared_ptr<Buffer>& vertex_buffer);

  void SetIndexBuffer(const std::shared_ptr<Buffer>& index_buffer);

  void SetDepthStencil(const DepthStencilDescriptor& descriptor);

  void SetReferenceValue(unsigned int value);

  void SetReferenceValue(unsigned int front_value, unsigned int back_value);

  void SetBlendColor(float r, float g, float b, float a);

  void SetViewport(int x, int y, unsigned int width, unsigned int height);

  void SetScissor(int x, int y, unsigned int width, unsigned int height);

  void SetCullMode(CullMode mode);

  void SetWindingMode(WindingMode mode);

  void DrawArrays(PrimitiveType primitive_type, std::size_t start, std::size_t count);

  void DrawElements(PrimitiveType primitive_type,
                    IndexFormat index_format,
                    std::size_t offset,
                    std::size_t count);

 private:
  void PrepareDrawing();

  void PrepareRenderPassDescriptor();

  void PrepareProgramState();

  void PrepareBlendMode();

  void PrepareBuffers();

  void PrepareDepthStencil();

  void AfterDraw();

  std::size_t render_pass_id_ = 0;
  EndRenderPassCallback callback_ = {};

  RenderPassDescriptor render_pass_descriptor_;

  std::shared_ptr<ProgramState> program_state_ = nullptr;

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

  float blend_color_red_ = 0.0f;
  float blend_color_green_ = 0.0f;
  float blend_color_blue_ = 0.0f;
  float blend_color_alpha_ = 0.0f;

  Region viewport_;
  Region scissor_;

  CullMode cull_mode_ = CullMode::kBack;
  WindingMode winding_mode_ = WindingMode::kCounterClockWise;

  DrawMethod draw_method_ = DrawMethod::kArrays;
  PrimitiveType primitive_type_ = PrimitiveType::kTriangles;
  std::size_t first_vertex_or_index_ = 0;
  std::size_t vertex_or_index_count_ = 0;
  IndexFormat index_format_ = IndexFormat::kUnsignedShort;

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
