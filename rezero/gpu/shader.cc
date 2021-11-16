// Created by Dong Zhong on 2021/11/16.

#include "rezero/gpu/shader.h"

namespace rezero {
namespace gpu {

Shader::Shader(ShaderStage stage, const std::string& source)
    : stage_(stage), shader_source_(source) {}

Shader::~Shader() = default;

} // namespace gpu
} // namespace rezero
