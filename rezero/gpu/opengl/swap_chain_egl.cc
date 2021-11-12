// Created by Dong Zhong on 2021/11/14.

#include "rezero/gpu/opengl/swap_chain_egl.h"

#include "rezero/base/logging.h"

namespace rezero {
namespace gpu {

SwapChainEGL::SwapChainEGL(EGLSurface surface)
    : surface_(surface) {
  REZERO_DCHECK(surface_ != EGL_NO_SURFACE);
  is_valid_ = true;
}

SwapChainEGL::~SwapChainEGL() = default;

} // namespace gpu
} // namespace rezero