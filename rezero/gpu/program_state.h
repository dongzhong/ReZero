// Created by Dong Zhong on 2021/10/28.

#ifndef REZERO_GPU_PROGRAM_STATE_H_
#define REZERO_GPU_PROGRAM_STATE_H_

#include <unordered_map>

#include "rezero/base/macros.h"
#include "rezero/gpu/program.h"
#include "rezero/gpu/vertex_layout.h"

namespace rezero {
namespace gpu {

struct TextureInfo {
  int location = 0;
  uint32_t slot = 0;
  std::shared_ptr<Texture> texture = nullptr;
};

class ProgramState {
 public:
  ProgramState(const std::shared_ptr<Program>& program);
  ~ProgramState();

  UniformInfo GetUniformInfo(const std::string& uniform_name) const;

  AttributeInfo GetAttributeInfo(const std::string& attribute_name) const;

  void SetUniform(const UniformInfo& uniform_info,
                  const void* data,
                  std::size_t data_size);

  void SetUniform(const UniformInfo& uniform_info,
                  uint32_t slot,
                  const std::shared_ptr<Texture>& texture);

  std::shared_ptr<VertexLayout> GetVertexLayout() const { return vertex_layout_; }

  std::shared_ptr<Program> GetProgram() const { return program_; }

  char* GetVertexUniformBufferPtr() const { return vertex_uniform_buffer_.get(); }

  const std::unordered_map<int, TextureInfo>& GetVertexUniformTextures() const {
    return vertex_uniform_textures_;
  }

 private:
  void SetVertexUniform(int location, std::size_t offset, const void* data, std::size_t data_size);

  void SetFragmentUniform(int location, const void* data, std::size_t data_size);

  void SetVertexUniform(int location, uint32_t slot, const std::shared_ptr<Texture>& texture);

  void SetFragmentUniform(int location, uint32_t slot, const std::shared_ptr<Texture>& texture);

  std::shared_ptr<Program> program_;

  std::unique_ptr<char[]> vertex_uniform_buffer_ = nullptr;
  std::unordered_map<int, TextureInfo> vertex_uniform_textures_ = {};

  // For Metal, fragment_uniform_buffer_ and fragment_uniform_textures_ here.

  std::shared_ptr<VertexLayout> vertex_layout_ = std::make_shared<VertexLayout>();

  REZERO_DISALLOW_COPY_AND_ASSIGN(ProgramState);
};

} // namespace gpu
} // namespace rezero

#endif // REZERO_GPU_PROGRAM_STATE_H_
