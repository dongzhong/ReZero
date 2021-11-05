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
  render_pass_id_ = id;
}

void RenderPassGL::SetEndRenderPassCallback(const EndRenderPassCallback& callback) {
  callback_ = callback;
}

void RenderPassGL::EndRenderPass() {
  if (callback_) {
    callback_(render_pass_id_);
  }
}

void RenderPassGL::PerformDrawing() {
  // TODO:
  PrepareDrawing();

  AfterDraw();
}

void RenderPassGL::SetRenderPassDescriptor(const RenderPassDescriptor& descriptor) {
  render_pass_descriptor_ = descriptor;
}

void RenderPassGL::PrepareDrawing() {
  // TODO:
  PrepareRenderPassDescriptor();
}

void RenderPassGL::PrepareRenderPassDescriptor() {
  auto& state_machine = StateMachineGL::GetCurrent();

  bool need_color_attachment = render_pass_descriptor_.need_color_attachment &&
                               (render_pass_descriptor_.color_attachment_texture_ != nullptr);
  bool need_depth_attachment = render_pass_descriptor_.enable_depth_test &&
                               (render_pass_descriptor_.depth_attachment_texture_ != nullptr);
  bool need_stencil_attachment = render_pass_descriptor_.enable_stencil_test &&
                                 (render_pass_descriptor_.stencil_attachment_texture_ != nullptr);
  if (need_color_attachment || need_depth_attachment || need_stencil_attachment) {
    origin_framebuffer_ = state_machine.GetCurrentBoundFramebuffer();
    glGenFramebuffers(1, &curren_framebuffer_);
    REZERO_DCHECK(curren_framebuffer_ > 0);
    glBindFramebuffer(GL_FRAMEBUFFER, curren_framebuffer_);
  }

  if (need_color_attachment) {
    auto internal_texture =
        render_pass_descriptor_.color_attachment_texture_->GetInteralTexture();
    glFramebufferTexture2D(GL_FRAMEBUFFER,
                           GL_COLOR_ATTACHMENT0,
                           GL_TEXTURE_2D,
                           internal_texture.texture_name_,
                           0);
  }

  if (need_depth_attachment) {
    auto internal_texture =
        render_pass_descriptor_.depth_attachment_texture_->GetInteralTexture();
    glFramebufferTexture2D(GL_FRAMEBUFFER,
                           GL_DEPTH_ATTACHMENT,
                           GL_TEXTURE_2D,
                           internal_texture.texture_name_,
                           0);
  }

  if (need_stencil_attachment) {
    auto internal_texture =
        render_pass_descriptor_.stencil_attachment_texture_->GetInteralTexture();
    glFramebufferTexture2D(GL_FRAMEBUFFER,
                           GL_STENCIL_ATTACHMENT,
                           GL_TEXTURE_2D,
                           internal_texture.texture_name_,
                           0);
  }

  if (curren_framebuffer_ > 0) {
    REZERO_DCHECK(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        << "Current framebuffer is not complete.";
  }

  CHECK_GL_ERROR_DEBUG();

  GLbitfield mask = 0;
  if (render_pass_descriptor_.need_clear_color) {
    state_machine.SetClearColorValue(render_pass_descriptor_.clear_color_value);
    mask |= GL_COLOR_BUFFER_BIT;
  }

  if (render_pass_descriptor_.need_clear_depth) {
    state_machine.SetClearDepthValue(render_pass_descriptor_.clear_depth_value);
    mask |= GL_DEPTH_BUFFER_BIT;
  }

  if (render_pass_descriptor_.need_clear_stencil) {
    state_machine.SetClearStencilValue(render_pass_descriptor_.clear_stencil_value);
    mask |= GL_STENCIL_BUFFER_BIT;
  }

  if (mask != 0) {
    glClear(mask);
  }
}

void RenderPassGL::AfterDraw() {
  // TODO:
  if (curren_framebuffer_ > 0) {
    // Use non-default framebuffer.
    glBindFramebuffer(GL_FRAMEBUFFER, origin_framebuffer_);
  }
}

} // namespace opengl

using RenderPassImplType = ImplType<RenderPass>::type;

static void ApplyRenderPassDescriptor(const RenderPassDescriptor& descriptor,
                                      const std::shared_ptr<RenderPassImplType>& render_pass) {
  render_pass->SetRenderPassDescriptor(descriptor);
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
