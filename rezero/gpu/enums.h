// Created by Dong Zhong on 2021/11/12.

#ifndef REZERO_GPU_ENUMS_H_
#define REZERO_GPU_ENUMS_H_

#include <cstdint>

namespace rezero {
namespace gpu {

enum class RenderingApi : uint32_t {
  kDefault,
  kOpenGL,
};

enum class BufferType : uint32_t {
  kVertex,
  kIndex,
};

enum class BufferUsage : uint32_t {
  kStatic,
  kDynamic,
};

enum class ShaderStage : uint32_t {
  kVertex,
  kFragment,
};

enum class TextureType : uint32_t {
  kTexture2D,
  kTextureCube,
};

enum class PixelFormat : uint32_t {
  kRGBA8888,
  kRGB888,
};

enum class SamplerFilter : uint32_t {
  kLinear,
  kLinearMipmapLeaner,
  kLinearMipmapNearest,
  kNearest,
  kNearestMipmapLinear,
  kNearestMipmapNearst,
};

enum class SamplerAddressMode : uint32_t {
  kRepeat,
  kMirroredRepeat,
  kClampToEdge,
};

enum class TextureCubeFace : uint32_t {
  kPositiveX = 0,
  kNegativeX = 1,
  kPositiveY = 2,
  kNegativeY = 3,
  kPositiveZ = 4,
  kNegativeZ = 5,
};

} // namespace gpu
} // namespace rezero

#endif // REZERO_GPU_ENUMS_H_
