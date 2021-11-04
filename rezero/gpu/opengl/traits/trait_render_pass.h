// Created by Dong Zhong on 2021/11/03.

#ifndef REZERO_GPU_OPENGL_TRAITS_TRAIT_RENDER_PASS_H_
#define REZERO_GPU_OPENGL_TRAITS_TRAIT_RENDER_PASS_H_

#include "rezero/gpu/opengl/includes.h"
#include "rezero/gpu/types.h"

namespace rezero {
namespace gpu {

namespace opengl {

struct RenderPassGL {
  // TODO:
};

} // namespace opengl

template <>
struct ImplType<RenderPass> {
  using type = opengl::RenderPassGL;
};

} // namespace gpu
} // namespace rezero

#endif // REZERO_GPU_OPENGL_TRAITS_TRAIT_RENDER_PASS_H_
