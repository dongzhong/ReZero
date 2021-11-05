// Created by Dong Zhong on 2021/11/05.

#include "rezero/gpu/render_pass_descriptor.h"
#include "rezero/gpu/texture.h"

namespace rezero {
namespace gpu {

RenderPassDescriptor& RenderPassDescriptor::operator=(const RenderPassDescriptor& other) {
  need_clear_color = other.need_clear_color;
  need_clear_depth = other.need_clear_depth;
  need_clear_stencil = other.need_clear_stencil;

  clear_color_value = other.clear_color_value;
  clear_depth_value = other.clear_depth_value;
  clear_stencil_value = other.clear_stencil_value;

  need_color_attachment = other.need_color_attachment;
  enable_depth_test = other.enable_depth_test;
  enable_stencil_test = other.enable_stencil_test;

  color_attachment_texture_ = other.color_attachment_texture_;
  depth_attachment_texture_ = other.depth_attachment_texture_;
  stencil_attachment_texture_ = other.stencil_attachment_texture_;

  return *this;
}

} // namespace gpu
} // namespace rezero
