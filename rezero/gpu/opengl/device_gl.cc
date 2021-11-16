// Created by Dong Zhong on 2021/11/15.

#include "rezero/gpu/opengl/device_gl.h"

#include "rezero/gpu/opengl/buffer_gl.h"
#include "rezero/gpu/opengl/program_gl.h"
#include "rezero/gpu/opengl/shader_gl.h"
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

std::shared_ptr<Shader> DeviceGL::CreateNewShader(ShaderStage stage, const std::string& source) {
  return std::make_shared<ShaderGL>(stage, source);
}

std::shared_ptr<Program> DeviceGL::CreateNewProgram(const std::shared_ptr<Shader>& vertex_shader,
                                                    const std::shared_ptr<Shader>& fragment_shader) {
  return std::make_shared<ProgramGL>(vertex_shader, fragment_shader);
}

} // namespace gpu
} // namespace rezero
