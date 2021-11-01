// Created by Dong Zhong on 2021/10/28.

#ifndef REZERO_GPU_PROGRAM_H_
#define REZERO_GPU_PROGRAM_H_

#include "rezero/gpu/shader.h"
#include REZERO_GPU_BACKEND(program.h)

namespace rezero {
namespace gpu {

class Program {
 public:
  Program(const std::shared_ptr<Shader>& vertex_shader,
          const std::shared_ptr<Shader>& fragment_shader);
  ~Program();

  UniformInfo GetUniformInfo(const std::string& name);

  AttributeInfo GetAttributeInfo(const std::string& name);

  bool IsValid() const { return is_valid_; }

 private:
  using InternalProgram = ImplType<Program>::type;
  InternalProgram program_;

  std::shared_ptr<Shader> vertex_shader_;
  std::shared_ptr<Shader> fragment_shader_;

  bool is_valid_ = false;

  REZERO_DISALLOW_COPY_AND_ASSIGN(Program);
};

} // namespace gpu
} // namespace rezero

#endif // REZERO_GPU_PROGRAM_H_
