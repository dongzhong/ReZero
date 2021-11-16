// Created by Dong Zhong on 2021/11/15.

#include "rezero/gpu/opengl/device_gl.h"

#include "rezero/gpu/opengl/buffer_gl.h"
#include "rezero/gpu/opengl/state_machine_gl.h"

namespace rezero {
namespace gpu {

DeviceGL::DeviceGL() {
  StateMachineGL::EnsureInitializedForCurrentThread();
}

DeviceGL::~DeviceGL() = default;

std::shared_ptr<Buffer> DeviceGL::CreateNewBuffer(BufferType type,
                                                  BufferUsage usage,
                                                  std::size_t size) {
  return std::make_shared<BufferGL>(type, usage, size);
}

} // namespace gpu
} // namespace rezero
