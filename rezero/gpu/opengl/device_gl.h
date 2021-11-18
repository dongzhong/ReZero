// Created by Dong Zhong on 2021/11/15.

#ifndef REZERO_GPU_OPENGL_DEVICE_GL_H_
#define REZERO_GPU_OPENGL_DEVICE_GL_H_

#include "rezero/gpu/device.h"

namespace rezero {
namespace gpu {

class DeviceGL final : public Device {
 public:
  DeviceGL();
  ~DeviceGL() override;

  std::shared_ptr<Buffer> CreateNewBuffer(BufferType type, BufferUsage usage, std::size_t size) override;

  std::shared_ptr<Shader> CreateNewShader(ShaderStage stage, const std::string& source) override;

  std::shared_ptr<Program> CreateNewProgram(const std::shared_ptr<Shader>& vertex_shader,
                                            const std::shared_ptr<Shader>& fragment_shader) override;

  std::shared_ptr<Texture> CreateNewTexture(const TextureDescriptor& descriptor) override;

 private:
  REZERO_DISALLOW_COPY_AND_ASSIGN(DeviceGL);
};

} // namespace gpu
} // namespace rezero

#endif // REZERO_GPU_OPENGL_DEVICE_GL_H_
