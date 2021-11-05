// Created by Dong Zhong on 2021/10/28.

#include "rezero/gpu/command_buffer.h"

#include "rezero/base/logging.h"

namespace rezero {
namespace gpu {

namespace opengl {

CommandBufferGL::CommandBufferGL() {
  // TODO:
}

CommandBufferGL::~CommandBufferGL() {
  // TODO:
}

void CommandBufferGL::AddNewRenderPass(std::size_t id, const std::shared_ptr<RenderPass>& render_pass) {
  render_passes_[id] = render_pass;
}

std::size_t CommandBufferGL::GetCurrentRenderPassId() {
  return ++current_render_pass_id_;
}

void CommandBufferGL::RenderPassReady(std::size_t render_pass_id) {
  if (auto iter = render_passes_.find(render_pass_id);
      iter != render_passes_.end()) {
    ready_render_passes_.push_back(render_pass_id);
  }
}

void CommandBufferGL::CommitAllReadyRenderPasses() {
  for (std::size_t id : ready_render_passes_) {
    auto render_pass = render_passes_[id];
    if (render_pass) {
      auto internal_render_pass = render_pass->GetInternalRenderPass();
      internal_render_pass->PerformDrawing();

      render_passes_.erase(id);
    }
  }
  ready_render_passes_.clear();
}

} // namespace opengl

CommandBuffer::CommandBuffer()
    : command_buffer_(std::make_shared<InternalCommandBuffer>()) {
  REZERO_DCHECK(command_buffer_);
}

CommandBuffer::~CommandBuffer() = default;

void CommandBuffer::BeginFrame() {
  // TODO:
}

std::shared_ptr<RenderPass> CommandBuffer::BeginRenderPass(
    const RenderPassDescriptor& descriptor) {
  auto render_pass = std::make_shared<RenderPass>(descriptor);
  auto id = command_buffer_->GetCurrentRenderPassId();
  auto internal_render_pass = render_pass->GetInternalRenderPass();
  internal_render_pass->SetRenderPassId(id);
  internal_render_pass->SetEndRenderPassCallback(
      [weak_command_buffer = command_buffer_->weak_from_this()](std::size_t render_pass_id) {
        if (auto shared_command_buffer = weak_command_buffer.lock()) {
          shared_command_buffer->RenderPassReady(render_pass_id);
        }
      });
  command_buffer_->AddNewRenderPass(id, render_pass);
  return render_pass;
}

void CommandBuffer::EndFrame() {
  // TODO:
  command_buffer_->CommitAllReadyRenderPasses();
}

} // namespace gpu
} // namespace rezero
