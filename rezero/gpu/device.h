// Created by Dong Zhong on 2021/11/15.

#ifndef REZERO_GPU_DEVICE_H_
#define REZERO_GPU_DEVICE_H_

#include <memory>

#include "rezero/base/macros.h"
#include "rezero/gpu/enums.h"
#include "rezero/gpu/types.h"

namespace rezero {
namespace gpu {

class Device {
 public:
  Device();
  virtual ~Device();

  virtual std::shared_ptr<Buffer> CreateNewBuffer(BufferType type, BufferUsage usage, std::size_t size) = 0;

  virtual std::shared_ptr<Shader> CreateNewShader(ShaderStage stage, const std::string& source) = 0;

  virtual std::shared_ptr<Program> CreateNewProgram(const std::shared_ptr<Shader>& vertex_shader,
                                                    const std::shared_ptr<Shader>& fragment_shader) = 0;

 private:
  REZERO_DISALLOW_COPY_AND_ASSIGN(Device);
};

} // namespace gpu
} // namespace rezero

#endif // REZERO_GPU_DEVICE_H_
