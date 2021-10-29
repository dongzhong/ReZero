// Created by Dong Zhong on 2021/10/28.

#ifndef REZERO_GPU_RENDER_PIPELINE_H_
#define REZERO_GPU_RENDER_PIPELINE_H_

#include "rezero/gpu/defines.h"
#include REZERO_GPU_BACKEND(render_pipeline.h)

namespace rezero {
namespace gpu {

class RenderPipeline {
 public:
  RenderPipeline();
  ~RenderPipeline();

 private:
  using InternalRenderPipeline = ImplType<RenderPipeline>::type;
  InternalRenderPipeline render_pipeline_;

  REZERO_DISALLOW_COPY_AND_ASSIGN(RenderPipeline);
};

} // namespace gpu
} // namespace rezero

#endif // REZERO_GPU_RENDER_PIPELINE_H_
