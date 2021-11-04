// Created by Dong Zhong on 2021/11/03.

#ifndef REZERO_GPU_RENDER_PASS_H_
#define REZERO_GPU_RENDER_PASS_H_

#include <array>

#include "rezero/base/macros.h"
#include "rezero/gpu/buffer.h"
#include "rezero/gpu/defines.h"
#include "rezero/gpu/depth_stencil_state.h"
#include "rezero/gpu/render_pipeline.h"
#include REZERO_GPU_BACKEND(render_pass.h)

namespace rezero {
namespace gpu {

struct RenderPassDescriptor {
  bool need_clear_color = false;
  bool need_clear_depth = false;
  bool need_clear_stencil = false;

  std::array<float, 4> clear_color_value { { 0.0f, 0.0f, 0.0f, 0.0f } };
  float clear_depth_value = 0.0f;
  float clear_stencil_value = 0.0f;
};

class RenderPass {
 public:
  RenderPass(const RenderPassDescriptor& descriptor);
  ~RenderPass();

  void SetRenderPiple(const std::shared_ptr<RenderPipeline>& render_pipeline);

  void SetVertexBuffer(const std::shared_ptr<Buffer>& buffer);

  void SetIndexBuffer(const std::shared_ptr<Buffer>& buffer);

  void SetDepthStencilState(const std::shared_ptr<DepthStencilState>& depth_stencil_state);

  void SetViewport(int x, int y, unsigned int width, unsigned int height);

  // TODO:
  // virtual void setCullMode(CullMode mode);
  // virtual void setWinding(Winding winding);

  void DrawArrays(PrimitiveType primitive_type, std::size_t start, std::size_t count);

  void DrawElements(PrimitiveType primitive_type, IndexFormat index_format, std::size_t offset, std::size_t count);

  void EndRenderPass();

  bool IsEnd() const { return is_end_; }

 private:
  using InternalRenderPass = ImplType<RenderPass>::type;
  InternalRenderPass render_pass_;

  bool is_end_ = false;

  REZERO_DISALLOW_COPY_AND_ASSIGN(RenderPass);
};

} // namespace gpu
} // namespace rezero

#endif // REZERO_GPU_RENDER_PASS_H_

