// Created by Dong Zhong on 2021/10/28.

#include "rezero/gpu/program_state.h"

#include "rezero/base/logging.h"

namespace rezero {
namespace gpu {

ProgramState::ProgramState(const std::shared_ptr<Program>& program)
    : program_(program) {
  REZERO_DCHECK(program_ && program_->IsValid());

  auto uniform_buffer_size = program_->program_.uniform_buffer_size_;
  vertex_uniform_buffer_ = std::make_unique<char[]>(uniform_buffer_size);
}

ProgramState::~ProgramState() = default;

UniformInfo ProgramState::GetUniformInfo(const std::string& uniform_name) const {
  return program_->GetUniformInfo(uniform_name);
}

AttributeInfo ProgramState::GetAttributeInfo(const std::string& attribute_name) const {
  return program_->GetAttributeInfo(attribute_name);
}

void ProgramState::SetUniform(const UniformInfo& uniform_info,
                              const void* data,
                              std::size_t data_size) {
  switch (uniform_info.stage) {
    case ShaderStage::kVertex:
      SetVertexUniform(uniform_info.location[0], uniform_info.location[1], data, data_size);
      break;
    case ShaderStage::kFragment:
      SetFragmentUniform(uniform_info.location[1], data, data_size);
      break;
    default:
      break;
  }
}

void ProgramState::SetUniform(const UniformInfo& uniform_info,
                              uint32_t slot,
                              const std::shared_ptr<Texture>& texture) {
  switch (uniform_info.stage) {
    case ShaderStage::kVertex:
      SetVertexUniform(uniform_info.location[0], slot, texture);
      break;
    case ShaderStage::kFragment:
      SetFragmentUniform(uniform_info.location[1], slot, texture);
      break;
    default:
      break;
  }
}

void ProgramState::SetVertexUniform(int location,
                                    std::size_t offset,
                                    const void* data,
                                    std::size_t data_size) {
  // Note: For OpenGL backend, all uniforms are handled as Vertex uniforms.

  if (location < 0) {
    return;
  }

  memcpy(vertex_uniform_buffer_.get() + offset, data, data_size);
}

void ProgramState::SetFragmentUniform(int location, const void* data, std::size_t size) {
  // Note: Only Metal may care this.

  if (location < 0) {
    return;
  }
}

void ProgramState::SetVertexUniform(int location,
                                    uint32_t slot,
                                    const std::shared_ptr<Texture>& texture) {
  // Note: For OpenGL backend, all uniforms are handled as Vertex uniforms.

  if (location < 0) {
    return;
  }

  auto& texture_info = vertex_uniform_textures_[location];
  texture_info.location = location;
  texture_info.slot = slot;
  texture_info.texture = texture;
}

void ProgramState::SetFragmentUniform(int location,
                                      uint32_t slot,
                                      const std::shared_ptr<Texture>& texture) {
  // Note: Only Metal may care this.

  if (location < 0) {
    return;
  }
}

} // namespace gpu
} // namespace rezero
