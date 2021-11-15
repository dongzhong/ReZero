// Created by Dong Zhong on 2021/11/14.

#include "rezero/gpu/opengl/swap_chain_eagl.h"

#include "rezero/base/logging.h"

namespace rezero {
namespace gpu {

SwapChainEAGL::SwapChainEAGL(const scoped_nsobject<CAEAGLLayer>& layer)
    : gl_layer_(layer) {
  REZERO_DCHECK(gl_layer_ != nullptr);
  is_valid_ = true;
  CGRect rect = gl_layer_.get().bounds;
  size_ = { (int) rect.size.width, (int) rect.size.height };
}

SwapChainEAGL::~SwapChainEAGL() = default;

CAEAGLLayer* SwapChainEAGL::GetGLLayer() const {
  return gl_layer_.get();
}

} // namespace gpiu
} // namespace rezero
