// Created by Dong Zhong on 2021/11/14.

#ifndef REZERO_GPU_OPENGL_SWAP_CHAIN_EAGL_H_
#define REZERO_GPU_OPENGL_SWAP_CHAIN_EAGL_H_

#import <QuartzCore/CAEAGLLayer.h>

#include "rezero/base/ios/scoped_nsobject.h"
#include "rezero/gpu/swap_chain.h"

namespace rezero {
namespace gpu {

class SwapChainEAGL : public SwapChain {
 public:
  SwapChainEAGL(const scoped_nsobject<CAEAGLLayer>& layer);
  ~SwapChainEAGL() override;

  CAEAGLLayer* GetGLLayer() const;

 private:
  scoped_nsobject<CAEAGLLayer> gl_layer_;

  REZERO_DISALLOW_COPY_AND_ASSIGN(SwapChainEAGL);
};

} // namespace gpiu
} // namespace rezero

#endif // REZERO_GPU_OPENGL_SWAP_CHAIN_EAGL_H_
