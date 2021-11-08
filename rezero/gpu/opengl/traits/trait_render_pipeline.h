// Created by Dong Zhong on 2021/10/28.

#ifndef REZERO_GPU_OPENGL_TRAITS_TRAIT_RENDER_PIPELINE_H_
#define REZERO_GPU_OPENGL_TRAITS_TRAIT_RENDER_PIPELINE_H_

#include "rezero/gpu/opengl/includes.h"
#include "rezero/gpu/types.h"

namespace rezero {
namespace gpu {

namespace opengl {

struct RenderPipelineGL {
  std::shared_ptr<ProgramState> program_state_ = nullptr;

  BlendDescriptor blend_descriptor_;
};

} // namespace opengl

template <>
struct ImplType<RenderPipeline> {
  using type = opengl::RenderPipelineGL;
};

} // namespace gpu
} // namespace rezero

#endif // REZERO_GPU_OPENGL_TRAITS_TRAIT_RENDER_PIPELINE_H_
