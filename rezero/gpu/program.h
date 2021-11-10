// Created by Dong Zhong on 2021/10/28.

#ifndef REZERO_GPU_PROGRAM_H_
#define REZERO_GPU_PROGRAM_H_

#include "rezero/gpu/shader.h"
#include REZERO_GPU_BACKEND(program.h)

namespace rezero {
namespace gpu {

class ProgramState;

class Program {
 public:
  using InternalProgram = ImplType<Program>::type;

  Program(const std::shared_ptr<Shader>& vertex_shader,
          const std::shared_ptr<Shader>& fragment_shader);
  ~Program();

  UniformInfo GetUniformInfo(const std::string& name);

  AttributeInfo GetAttributeInfo(const std::string& name);

  bool IsValid() const { return is_valid_; }

  std::unordered_map<std::string, UniformInfo> GetUniforms() const { return program_.uniforms_; }
  std::unordered_map<std::string, AttributeInfo> GetAttributes() const { return program_.attributes_; }

  const InternalProgram& GetInternalProgram() const { return program_; }

 private:
  InternalProgram program_;

  std::shared_ptr<Shader> vertex_shader_;
  std::shared_ptr<Shader> fragment_shader_;

  bool is_valid_ = false;

  friend class ProgramState;

  REZERO_DISALLOW_COPY_AND_ASSIGN(Program);
};

} // namespace gpu
} // namespace rezero

#endif // REZERO_GPU_PROGRAM_H_
