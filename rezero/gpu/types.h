// Created by Dong Zhong on 2021/11/12.

#ifndef REZERO_GPU_TYPES_H_
#define REZERO_GPU_TYPES_H_

#include "rezero/gpu/enums.h"

namespace rezero {
namespace gpu {

class Context;
class SwapChain;

class Device;

class Buffer;
class Texture;
class Pipeline;
class RenderPass;
class Shader;
class Program;
class VertexLayout;

struct SamplerDescriptor {
  SamplerDescriptor() = default;
  SamplerDescriptor(const SamplerDescriptor& other);

  SamplerDescriptor& operator=(const SamplerDescriptor& other);

  bool operator==(const SamplerDescriptor& other) const;
  bool operator!=(const SamplerDescriptor& other) const;

  SamplerFilter mag_filter = SamplerFilter::kLinear;
  SamplerFilter min_filter = SamplerFilter::kLinear;

  SamplerAddressMode s_address_mode = SamplerAddressMode::kRepeat;
  SamplerAddressMode t_address_mode = SamplerAddressMode::kRepeat;
};

} // namespace gpu
} // namespace rezero

#endif // REZERO_GPU_TYPES_H_
