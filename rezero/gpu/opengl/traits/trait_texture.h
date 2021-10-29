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
};

} // namespace opengl

template <>
struct ImplType<Texture> {
  using type = opengl::TextureGL;
};

} // namespace gpu
} // namespace rezero

#endif // REZERO_GPU_OPENGL_TRAITS_TRAIT_TEXTURE_H_
