// Created by Dong Zhong on 2021/10/28.

#ifndef REZERO_GPU_DEPTH_STENCIL_STATE_H_
#define REZERO_GPU_DEPTH_STENCIL_STATE_H_

#include "rezero/base/macros.h"
#include "rezero/gpu/types.h"

namespace rezero {
namespace gpu {

struct StencilDescriptor {
  StencilDescriptor();
  StencilDescriptor(const StencilDescriptor& other);
  StencilDescriptor& operator=(const StencilDescriptor& other);

  CompareFunction stencil_compare_function = CompareFunction::kAlways;

  StencilOperation stencil_failed_operation = StencilOperation::kKeep;
  StencilOperation depth_failed_operation = StencilOperation::kKeep;
  StencilOperation test_pass_operation = StencilOperation::kKeep;
  unsigned int read_mask = -1;
  unsigned int write_mask = -1;
};

struct DepthStencilDescriptor {
  DepthStencilDescriptor();
  DepthStencilDescriptor(const DepthStencilDescriptor& other);
  DepthStencilDescriptor& operator=(const DepthStencilDescriptor& other);

  bool enable_depth_test = false;
  CompareFunction depth_compare_function = CompareFunction::kLess;
  bool depth_write_enable = true;

  bool enable_stencil_test = false;
  StencilDescriptor front_stencil_descriptor;
  StencilDescriptor back_stencil_descriptor;
};

class DepthStencilState {
 public:
  DepthStencilState(const DepthStencilDescriptor& descriptor);
  ~DepthStencilState();

  const DepthStencilDescriptor& GetDescripotr() const { return descriptor_; }

 private:
  DepthStencilDescriptor descriptor_;

  REZERO_DISALLOW_COPY_AND_ASSIGN(DepthStencilState);
};

} // namespace gpu
} // namespace rezero

#endif // REZERO_GPU_DEPTH_STENCIL_STATE_H_
