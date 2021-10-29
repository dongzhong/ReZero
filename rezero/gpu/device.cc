// Created by Dong Zhong on 2021/10/28.

#include "rezero/gpu/device.h"

namespace rezero {
namespace gpu {

std::shared_ptr<Device> Device::Create() {
  return std::make_shared<Device>();
}

Device::Device() = default;

Device::~Device() = default;

std::shared_ptr<Buffer> Device::MakeNewBuffer() {
  return std::make_shared<Buffer>();
}

std::shared_ptr<CommandBuffer> Device::MakeNewCommandBuffer() {
  return std::make_shared<CommandBuffer>();
}

std::shared_ptr<DepthStencilState> Device::MakeNewDepthStencilState() {
  return std::make_shared<DepthStencilState>();
}

std::shared_ptr<Program> Device::MakeNewProgram() {
  return std::make_shared<Program>();
}

std::shared_ptr<RenderPipeline> Device::MakeNewRenderPipeline() {
  return std::make_shared<RenderPipeline>();
}

std::shared_ptr<Texture> Device::MakeNewTexture() {
  return std::make_shared<Texture>();
}

} // namespace gpu
} // namespace rezero
