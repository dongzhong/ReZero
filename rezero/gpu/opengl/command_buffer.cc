// Created by Dong Zhong on 2021/10/28.

#include "rezero/gpu/command_buffer.h"

#include "rezero/base/logging.h"

namespace rezero {
namespace gpu {

CommandBuffer::CommandBuffer() {
  // TODO:
}

CommandBuffer::~CommandBuffer() = default;

void CommandBuffer::BeginFrame() {
  // TODO:
}

std::shared_ptr<RenderPass> CommandBuffer::BeginRenderPass(
    const RenderPassDescriptor& descriptor) {
  return std::make_shared<RenderPass>(descriptor);
}

void CommandBuffer::EndFrame() {
  // TODO:
}

} // namespace gpu
} // namespace rezero
