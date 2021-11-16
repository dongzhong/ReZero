// Created by Dong Zhong on 2021/11/16.

#ifndef REZERO_GPU_SHADER_H_
#define REZERO_GPU_SHADER_H_

#include <string>

#include "rezero/base/macros.h"
#include "rezero/gpu/enums.h"

namespace rezero {
namespace gpu {

class Shader {
 public:
  Shader(ShaderStage stage, const std::string& source);
  virtual ~Shader();

  ShaderStage GetStage() const { return stage_; }

  bool IsValid() const { return is_valid_; }

 protected:
  ShaderStage stage_ = ShaderStage::kVertex;
  std::string shader_source_;

  bool is_valid_ = false;

 private:
  REZERO_DISALLOW_COPY_AND_ASSIGN(Shader);
};

} // namespace gpu
} // namespace rezero

#endif // REZERO_GPU_SHADER_H_
