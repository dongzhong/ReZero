// Created by Dong Zhong on 2021/10/28.

#ifndef REZERO_GPU_OPENGL_TRAITS_TRAIT_PROGRAM_H_
#define REZERO_GPU_OPENGL_TRAITS_TRAIT_PROGRAM_H_

#include <unordered_map>

#include "rezero/gpu/opengl/includes.h"
#include "rezero/gpu/types.h"

namespace rezero {
namespace gpu {

namespace opengl {

struct ProgramGL {
  GLuint program_name_ = 0;

  std::unordered_map<std::string, UniformInfo> uniforms_;
  std::unordered_map<std::string, AttributeInfo> attributes_;

  std::size_t uniform_buffer_size_ = 0;
};

} // namespace opengl

template <>
struct ImplType<Program> {
  using type = opengl::ProgramGL;
};

} // namespace gpu
} // namespace rezero

#endif // REZERO_GPU_OPENGL_TRAITS_TRAIT_PROGRAM_H_
