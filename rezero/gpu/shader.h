// Created by Dong Zhong on 2021/10/31.

#ifndef REZERO_GPU_SHADER_H_
#define REZERO_GPU_SHADER_H_

#include <string>

#include "rezero/gpu/defines.h"
#include "rezero/gpu/types.h"
#include REZERO_GPU_BACKEND(shader.h)

namespace rezero {
namespace gpu {

class Program;

class Shader {
 public:
  Shader(ShaderStage stage, const std::string& source);
  ~Shader();

  bool IsValid() const { return is_valid_; }

 private:
  using InternalShader = ImplType<Shader>::type;
  InternalShader shader_;

  ShaderStage stage_ = ShaderStage::kVertex;
  std::string source_;
  bool is_valid_ = false;

  friend class Program;

  REZERO_DISALLOW_COPY_AND_ASSIGN(Shader);
};

} // namespace gpu
} // namespace rezero

#endif // REZERO_GPU_SHADER_H_
