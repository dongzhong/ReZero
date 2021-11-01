// Created by Dong Zhong on 2021/10/28.

#include "rezero/gpu/device.h"
#include "rezero/gpu/opengl/state_machine_gl.h"

namespace rezero {
namespace gpu {

std::shared_ptr<Device> Device::Create() {
  return std::make_shared<Device>();
}

Device::Device() {
  StateMachineGL::EnsureInitializedForCurrentThread();
}

Device::~Device() = default;

std::shared_ptr<Buffer> Device::MakeNewBuffer(
    std::size_t size, BufferType type, BufferUsage usage) {
  return std::make_shared<Buffer>(size, type, usage);
}

std::shared_ptr<CommandBuffer> Device::MakeNewCommandBuffer() {
  return std::make_shared<CommandBuffer>();
}

std::shared_ptr<DepthStencilState> Device::MakeNewDepthStencilState() {
  return std::make_shared<DepthStencilState>();
}

std::shared_ptr<Program> Device::MakeNewProgram(
    const std::string& vertex_shader,
    const std::string& fragment_shader) {
  return std::make_shared<Program>(std::make_shared<Shader>(ShaderStage::kVertex, vertex_shader),
                                   std::make_shared<Shader>(ShaderStage::kFragment, fragment_shader));
}

std::shared_ptr<RenderPipeline> Device::MakeNewRenderPipeline() {
  return std::make_shared<RenderPipeline>();
}

std::shared_ptr<Texture> Device::MakeNewTexture(const TextureDescriptor& descriptor) {
  switch (descriptor.texture_type_) {
    case TextureType::kTexture2D:
      return std::make_shared<Texture2D>(descriptor);
    case TextureType::kTextureCube:
      return std::make_shared<TextureCube>(descriptor);
    default:
      return nullptr;
  }
}

std::shared_ptr<Shader> Device::MakeNewShader(ShaderStage stage, const std::string& source) {
  return std::make_shared<Shader>(stage, source);
}

} // namespace gpu
} // namespace rezero
