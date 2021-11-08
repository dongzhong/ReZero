// Created by Dong Zhong on 2021/10/31.

#include "rezero/gpu/types.h"

namespace rezero {
namespace gpu {

BlendDescriptor::BlendDescriptor(const BlendDescriptor& other)
    : blend_enable(other.blend_enable),
      alpha_blend_operation(other.alpha_blend_operation),
      src_alpha_blend_factor(other.src_alpha_blend_factor),
      src_rgb_blend_factor(other.src_rgb_blend_factor),
      dst_alpha_blend_factor(other.dst_alpha_blend_factor),
      dst_rgb_blend_factor(other.dst_rgb_blend_factor),
      color_mask(other.color_mask) {}

BlendDescriptor& BlendDescriptor::operator=(const BlendDescriptor& other) {
  blend_enable = other.blend_enable;
  alpha_blend_operation = other.alpha_blend_operation;
  src_alpha_blend_factor = other.src_alpha_blend_factor;
  src_rgb_blend_factor = other.src_rgb_blend_factor;
  dst_alpha_blend_factor = other.dst_alpha_blend_factor;
  dst_rgb_blend_factor = other.dst_rgb_blend_factor;
  color_mask = other.color_mask;

  return *this;
}

SamplerDescriptor& SamplerDescriptor::operator=(const SamplerDescriptor& other) {
  mag_filter = other.mag_filter;
  min_filter = other.min_filter;
  s_address_mode = other.s_address_mode;
  t_address_mode = other.t_address_mode;
  return *this;
}

bool SamplerDescriptor::operator==(const SamplerDescriptor& other) const {
  return (mag_filter == other.mag_filter &&
          min_filter == other.min_filter &&
          s_address_mode == other.s_address_mode &&
          t_address_mode == other.t_address_mode);
}

bool SamplerDescriptor::operator!=(const SamplerDescriptor& other) const {
  return !operator==(other);
}

} // namespace gpu
} // namespace rezero
