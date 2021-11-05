// Created by Dong Zhong on 2021/11/03.

#include "rezero/gpu/render_pass.h"

#include "rezero/base/logging.h"
#include "rezero/gpu/opengl/state_machine_gl.h"

namespace rezero {
namespace gpu {

namespace opengl {

RenderPassGL::RenderPassGL() {
  // TODO:
}

RenderPassGL::~RenderPassGL() {
  // TODO:
}

void RenderPassGL::SetRenderPassId(std::size_t id) {
  // TODO:
}

void RenderPassGL::SetEndRenderPassCallback(const EndRenderPassCallback& callback) {
  // TODO:
}

void RenderPassGL::EndRenderPass() {
  if (callback_) {
    callback_(render_pass_id_);
  }
}

void RenderPassGL::PerformDrawing() {
  // TODO:
  PrepareDrawing();
}

void RenderPassGL::SetNeedClearColor(bool need_clear_color) {
  need_clear_color_ = need_clear_color;
}

void RenderPassGL::SetNeedClearDepth(bool need_clear_depth) {
  need_clear_depth_ = need_clear_depth;
}

void RenderPassGL::SetNeedClearStencil(bool need_clear_stencil) {
  need_clear_stencil_ = need_clear_stencil;
}

void RenderPassGL::PrepareDrawing() {
  // TODO:
  auto& statue_machine = StateMachineGL::GetCurrent();
}

} // namespace opengl

using RenderPassImplType = ImplType<RenderPass>::type;

static void ApplyRenderPassDescriptor(const RenderPassDescriptor& descriptor,
                                      const std::shared_ptr<RenderPassImplType>& render_pass) {
  render_pass->SetNeedClearColor(descriptor.need_clear_color);
  render_pass->SetNeedClearDepth(descriptor.need_clear_depth);
  render_pass->SetNeedClearStencil(descriptor.need_clear_stencil);
}

RenderPass::RenderPass(const RenderPassDescriptor& descriptor)
    : render_pass_(std::make_shared<InternalRenderPass>()) {
  ApplyRenderPassDescriptor(descriptor, render_pass_);
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
  render_pass_->EndRenderPass();
}

} // namespace gpu
} // namespace rezero
