// Created by Dong Zhong on 2021/11/03.

#ifndef REZERO_GPU_RENDER_PASS_H_
#define REZERO_GPU_RENDER_PASS_H_

#include "rezero/base/macros.h"
#include "rezero/gpu/buffer.h"
#include "rezero/gpu/defines.h"
#include "rezero/gpu/depth_stencil_state.h"
#include "rezero/gpu/render_pass_descriptor.h"
#include "rezero/gpu/render_pipeline.h"
#include REZERO_GPU_BACKEND(render_pass.h)

namespace rezero {
namespace gpu {

class RenderPass {
 public:
  using InternalRenderPass = ImplType<RenderPass>::type;

  RenderPass(const RenderPassDescriptor& descriptor);
  ~RenderPass();

  void SetRenderPipeline(const std::shared_ptr<RenderPipeline>& render_pipeline);

  void SetVertexBuffer(const std::shared_ptr<Buffer>& buffer);

  void SetIndexBuffer(const std::shared_ptr<Buffer>& buffer);

  void SetDepthStencilState(const std::shared_ptr<DepthStencilState>& depth_stencil_state);

  void SetStencilReferenceValue(unsigned int value);

  void SetStencilReferenceValue(unsigned int front_value, unsigned int back_value);

  void SetBlendColor(float r, float g, float b, float a);

  void SetViewport(int x, int y, unsigned int width, unsigned int height);

  void SetScissor(bool enable, int x, int y, unsigned int width, unsigned int height);

  void SetCullMode(CullMode mode);

  void SetWinding(WindingMode mode);

  void DrawArrays(PrimitiveType primitive_type, std::size_t start, std::size_t count);

  void DrawElements(PrimitiveType primitive_type, IndexFormat index_format, std::size_t offset, std::size_t count);

  void EndRenderPass();

  bool IsEnd() const { return is_end_; }

  std::shared_ptr<InternalRenderPass> GetInternalRenderPass() const { return render_pass_; }

 private:
  std::shared_ptr<InternalRenderPass> render_pass_;

  bool is_end_ = false;

  REZERO_DISALLOW_COPY_AND_ASSIGN(RenderPass);
};

} // namespace gpu
} // namespace rezero

#endif // REZERO_GPU_RENDER_PASS_H_

