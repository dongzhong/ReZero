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

 private:
  REZERO_DISALLOW_COPY_AND_ASSIGN(DeviceGL);
};

} // namespace gpu
} // namespace rezero

#endif // REZERO_GPU_OPENGL_DEVICE_GL_H_
