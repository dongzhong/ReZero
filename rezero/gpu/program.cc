// Created by Dong Zhong on 2021/11/16.

#include "rezero/gpu/program.h"

#include "rezero/base/logging.h"
#include "rezero/gpu/shader.h"

namespace rezero {
namespace gpu {

Program::Program(const std::shared_ptr<Shader>& vertex_shader,
                 const std::shared_ptr<Shader>& fragment_shader)
    : vertex_shader_(vertex_shader),
      fragment_shader_(fragment_shader) {
  REZERO_DCHECK(vertex_shader_ != nullptr && vertex_shader_->IsValid());
  REZERO_DCHECK(fragment_shader_ != nullptr && fragment_shader_->IsValid());
}

Program::~Program() = default;

} // namespace gpu
} // namespace rezero
