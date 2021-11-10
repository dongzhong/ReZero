// Created by Dong Zhong on 2021/10/28.

#include "rezero/gpu/depth_stencil_state.h"

namespace rezero {
namespace gpu {

StencilDescriptor::StencilDescriptor() = default;

StencilDescriptor::StencilDescriptor(const StencilDescriptor& other)
    : stencil_compare_function(other.stencil_compare_function),
      stencil_failed_operation(other.stencil_failed_operation),
      depth_failed_operation(other.depth_failed_operation),
      test_pass_operation(other.test_pass_operation),
      read_mask(other.read_mask),
      write_mask(other.write_mask) {}

StencilDescriptor& StencilDescriptor::operator=(const StencilDescriptor& other) {
  stencil_compare_function = other.stencil_compare_function;

  stencil_failed_operation = other.stencil_failed_operation;
  depth_failed_operation = other.depth_failed_operation;
  test_pass_operation = other.test_pass_operation;

  read_mask = other.read_mask;
  write_mask = other.write_mask;

  return *this;
}

DepthStencilDescriptor::DepthStencilDescriptor() = default;

DepthStencilDescriptor::DepthStencilDescriptor(const DepthStencilDescriptor& other)
    : enable_depth_test(other.enable_depth_test),
      depth_compare_function(other.depth_compare_function),
      depth_write_enable(other.depth_write_enable),
      enable_stencil_test(other.enable_stencil_test),
      front_stencil_descriptor(other.front_stencil_descriptor),
      back_stencil_descriptor(other.back_stencil_descriptor) {}

DepthStencilDescriptor& DepthStencilDescriptor::operator=(
    const DepthStencilDescriptor& other) {
  enable_depth_test = other.enable_depth_test;
  depth_compare_function = other.depth_compare_function;
  depth_write_enable = other.depth_write_enable;

  enable_stencil_test = other.enable_stencil_test;
  front_stencil_descriptor = other.front_stencil_descriptor;
  back_stencil_descriptor = other.back_stencil_descriptor;

  return *this;
}

DepthStencilState::DepthStencilState(const DepthStencilDescriptor& descriptor)
    : descriptor_(descriptor) {}

DepthStencilState::~DepthStencilState() = default;

} // namespace gpu
} // namespace rezero
