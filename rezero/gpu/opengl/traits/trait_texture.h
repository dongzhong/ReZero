// Created by Dong Zhong on 2021/10/28.

#ifndef REZERO_GPU_OPENGL_TRAITS_TRAIT_TEXTURE_H_
#define REZERO_GPU_OPENGL_TRAITS_TRAIT_TEXTURE_H_

#include "rezero/gpu/opengl/includes.h"
#include "rezero/gpu/types.h"

namespace rezero {
namespace gpu {

namespace opengl {

struct TextureGL {
  GLuint texture_name_ = 0;

  GLenum texture_type_ = GL_TEXTURE_2D;

  GLint internal_format_ = GL_RGBA;
  GLenum format_ = GL_RGBA;
  GLenum data_type_ = GL_UNSIGNED_BYTE;

  GLenum mag_filter = GL_LINEAR;
  GLenum min_filter = GL_LINEAR;
  GLenum s_wrap_mode = GL_REPEAT;
  GLenum t_wrap_mode = GL_REPEAT;
  bool sampler_has_changed = true;

  void ApplySamplers();
};

} // namespace opengl

template <>
struct ImplType<Texture> {
  using type = opengl::TextureGL;
};

} // namespace gpu
} // namespace rezero

#endif // REZERO_GPU_OPENGL_TRAITS_TRAIT_TEXTURE_H_
