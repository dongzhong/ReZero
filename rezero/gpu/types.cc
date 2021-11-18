// Created by Dong Zhong on 2021/11/12.

#include "rezero/gpu/types.h"

namespace rezero {
namespace gpu {

SamplerDescriptor::SamplerDescriptor(const SamplerDescriptor& other)
    : mag_filter(other.mag_filter),
      min_filter(other.min_filter),
      s_address_mode(other.s_address_mode),
      t_address_mode(other.t_address_mode) {}

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
