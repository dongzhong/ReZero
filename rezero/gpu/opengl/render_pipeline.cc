// Created by Dong Zhong on 2021/10/28.

#include "rezero/gpu/render_pipeline.h"

#include "rezero/base/logging.h"

namespace rezero {
namespace gpu {

RenderPipeline::RenderPipeline(const RenderPipelineDescriptor& descriptor) {
  REZERO_DCHECK(descriptor.program_state);
  render_pipeline_.program_state_ = descriptor.program_state;
}

RenderPipeline::~RenderPipeline() = default;

} // namespace gpu
} // namespace rezero
