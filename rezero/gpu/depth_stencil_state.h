// Created by Dong Zhong on 2021/10/28.

#ifndef REZERO_GPU_DEPTH_STENCIL_STATE_H_
#define REZERO_GPU_DEPTH_STENCIL_STATE_H_

#include "rezero/base/macros.h"

namespace rezero {
namespace gpu {

class DepthStencilState {
 public:
  DepthStencilState();
  ~DepthStencilState();

 private:
  REZERO_DISALLOW_COPY_AND_ASSIGN(DepthStencilState);
};

} // namespace gpu
} // namespace rezero

#endif // REZERO_GPU_DEPTH_STENCIL_STATE_H_
