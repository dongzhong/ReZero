// Created by Dong Zhong on 2021/11/16.

#ifndef REZERO_GPU_PROGRAM_H_
#define REZERO_GPU_PROGRAM_H_

#include <string>

#include "rezero/base/macros.h"
#include "rezero/gpu/types.h"

namespace rezero {
namespace gpu {

class Program {
 public:
  Program(const std::shared_ptr<Shader>& vertex_shader, const std::shared_ptr<Shader>& fragment_shader);
  virtual ~Program();

  bool IsValid() const { return is_valid_; }

 protected:
  std::shared_ptr<Shader> vertex_shader_;
  std::shared_ptr<Shader> fragment_shader_;

  bool is_valid_ = false;

 private:
  REZERO_DISALLOW_COPY_AND_ASSIGN(Program);
};

} // namespace gpu
} // namespace rezero

#endif // REZERO_GPU_PROGRAM_H_
