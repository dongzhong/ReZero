// Created by Dong Zhong on 2021/10/28.

#ifndef REZERO_GPU_DEVICE_H_
#define REZERO_GPU_DEVICE_H_

#include <memory>

#include "rezero/base/macros.h"
#include "rezero/gpu/command_buffer.h"
#include "rezero/gpu/texture.h"

namespace rezero {
namespace gpu {

class Device {
 public:
  static std::shared_ptr<Device> Create();

  Device();
  ~Device();

  std::shared_ptr<Buffer> MakeNewBuffer(std::size_t size, BufferType type, BufferUsage usage);

  std::shared_ptr<CommandBuffer> MakeNewCommandBuffer();

  std::shared_ptr<DepthStencilState> MakeNewDepthStencilState(const DepthStencilDescriptor& descriptor);

  std::shared_ptr<Program> MakeNewProgram(const std::string& vertex_shader,
                                          const std::string& fragment_shader);

  std::shared_ptr<RenderPipeline> MakeNewRenderPipeline(const RenderPipelineDescriptor& descriptor);

  std::shared_ptr<Texture> MakeNewTexture(const TextureDescriptor& descriptor);

 private:
  std::shared_ptr<Shader> MakeNewShader(ShaderStage stage, const std::string& source);

  REZERO_DISALLOW_COPY_AND_ASSIGN(Device);
};

} // namespace gpu
} // namespace rezero

#endif // REZERO_GPU_DEVICE_H_
