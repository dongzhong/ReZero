// Created by Dong Zhong on 2021/10/28.

#ifndef REZERO_GPU_OPENGL_TRAITS_TRAIT_COMMAND_BUFFER_H_
#define REZERO_GPU_OPENGL_TRAITS_TRAIT_COMMAND_BUFFER_H_

#include "rezero/gpu/opengl/includes.h"
#include "rezero/gpu/types.h"

namespace rezero {
namespace gpu {

namespace opengl {

struct CommandBufferGL {
  // TODO:
};

} // namespace opengl

template <>
struct ImplType<CommandBuffer> {
  using type = opengl::CommandBufferGL;
};

} // namespace gpu
} // namespace rezero

#endif // REZERO_GPU_OPENGL_TRAITS_TRAIT_COMMAND_BUFFER_H_
