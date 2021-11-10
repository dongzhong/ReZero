// Created by Dong Zhong on 2021/10/28.

#ifndef REZERO_GPU_RENDER_PIPELINE_H_
#define REZERO_GPU_RENDER_PIPELINE_H_

#include "rezero/base/logging.h"
#include "rezero/gpu/defines.h"
#include "rezero/gpu/program_state.h"
#include REZERO_GPU_BACKEND(render_pipeline.h)

namespace rezero {
namespace gpu {

struct RenderPipelineDescriptor {
  RenderPipelineDescriptor() = default;

  RenderPipelineDescriptor(const RenderPipelineDescriptor& other)
      : program_state(other.program_state),
        blend_descriptor(other.blend_descriptor) {
    REZERO_DCHECK(program_state);
  }

  RenderPipelineDescriptor& operator=(const RenderPipelineDescriptor& other) {
    program_state = other.program_state;
    blend_descriptor = other.blend_descriptor;

    return *this;
  }

  std::shared_ptr<ProgramState> program_state = nullptr;

  BlendDescriptor blend_descriptor;
};

class RenderPipeline {
 public:
  RenderPipeline(const RenderPipelineDescriptor& descriptor);
  ~RenderPipeline();

 private:
  using InternalRenderPipeline = ImplType<RenderPipeline>::type;
  InternalRenderPipeline render_pipeline_;

  friend class RenderPass;

  REZERO_DISALLOW_COPY_AND_ASSIGN(RenderPipeline);
};

} // namespace gpu
} // namespace rezero

#endif // REZERO_GPU_RENDER_PIPELINE_H_
