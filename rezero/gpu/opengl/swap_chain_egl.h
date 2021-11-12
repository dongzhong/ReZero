// Created by Dong Zhong on 2021/11/14.

#ifndef REZERO_GPU_OPENGL_SWAP_CHAIN_EGL_H_
#define REZERO_GPU_OPENGL_SWAP_CHAIN_EGL_H_

#include <EGL/egl.h>

#include "rezero/gpu/swap_chain.h"

namespace rezero {
namespace gpu {

class SwapChainEGL : public SwapChain {
 public:
  SwapChainEGL(EGLSurface surface);
  ~SwapChainEGL() override;

  EGLSurface GetSurface() const { return surface_; }

 private:
  EGLSurface surface_ = EGL_NO_SURFACE;

  REZERO_DISALLOW_COPY_AND_ASSIGN(SwapChainEGL);
};

} // namespace gpu
} // namespace rezero

#endif // REZERO_GPU_OPENGL_SWAP_CHAIN_EGL_H_