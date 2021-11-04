// Created by Dong Zhong on 2021/11/03.

#include "rezero/gpu/render_pass.h"

#include "rezero/base/logging.h"

namespace rezero {
namespace gpu {

RenderPass::RenderPass(const RenderPassDescriptor& descriptor) {
  // TODO:
}

RenderPass::~RenderPass() = default;

void RenderPass::SetRenderPiple(const std::shared_ptr<RenderPipeline>& render_pipeline) {
  // TODO:
}

void RenderPass::SetVertexBuffer(const std::shared_ptr<Buffer>& buffer) {
  // TODO:
}

void RenderPass::SetIndexBuffer(const std::shared_ptr<Buffer>& buffer) {
  // TODO:
}

void RenderPass::SetDepthStencilState(
    const std::shared_ptr<DepthStencilState>& depth_stencil_state) {
  // TODO:
}

void RenderPass::SetViewport(int x, int y, unsigned int width, unsigned int height) {
  // TODO:
}

void RenderPass::DrawArrays(PrimitiveType primitive_type, std::size_t start, std::size_t count) {
  // TODO:
}

void RenderPass::DrawElements(PrimitiveType primitive_type,
                              IndexFormat index_format,
                              std::size_t offset,
                              std::size_t count) {
  // TODO:
}

void RenderPass::EndRenderPass() {
  is_end_ = true;
  // TODO:
}

} // namespace gpu
} // namespace rezero

