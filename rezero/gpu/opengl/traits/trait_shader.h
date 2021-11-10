// Created by Dong Zhong on 2021/10/31.

#ifndef REZERO_GPU_OPENGL_TRAITS_TRAIT_SHADER_H_
#define REZERO_GPU_OPENGL_TRAITS_TRAIT_SHADER_H_

#include "rezero/gpu/opengl/includes.h"
#include "rezero/gpu/types.h"

namespace rezero {
namespace gpu {

namespace opengl {

struct ShaderGL {
  GLuint shader_name_ = 0;

  GLenum shader_type_ = GL_VERTEX_SHADER;
};

} // namespace opengl

template <>
struct ImplType<Shader> {
  using type = opengl::ShaderGL;
};

} // namespace gpu
} // namespace rezero

#endif // REZERO_GPU_OPENGL_TRAITS_TRAIT_SHADER_H_
