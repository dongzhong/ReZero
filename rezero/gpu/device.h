// Created by Dong Zhong on 2021/10/28.

#ifndef REZERO_GPU_DEVICE_H_
#define REZERO_GPU_DEVICE_H_

#include <memory>

#include "rezero/base/macros.h"
#include "rezero/gpu/buffer.h"
#include "rezero/gpu/command_buffer.h"
#include "rezero/gpu/depth_stencil_state.h"
#include "rezero/gpu/program.h"
#include "rezero/gpu/program_state.h"
#include "rezero/gpu/render_pipeline.h"
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

  std::shared_ptr<DepthStencilState> MakeNewDepthStencilState();

  std::shared_ptr<Program> MakeNewProgram();

  std::shared_ptr<RenderPipeline> MakeNewRenderPipeline();

  std::shared_ptr<Texture> MakeNewTexture(const TextureDescriptor& descriptor);

 private:
  REZERO_DISALLOW_COPY_AND_ASSIGN(Device);
};

} // namespace gpu
} // namespace rezero

#endif // REZERO_GPU_DEVICE_H_
