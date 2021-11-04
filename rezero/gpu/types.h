// Created by Dong Zhong on 2021/10/28.

#ifndef REZERO_GPU_TYPES_H_
#define REZERO_GPU_TYPES_H_

#include <stdint.h>
#include <cstddef>

namespace rezero {
namespace gpu {

template <typename T>
struct ImplType {
  // using type = xxx
};

class Buffer;
class CommandBuffer;
class Program;
class RenderPass;
class RenderPipeline;
class Texture;
class Shader;

enum class BufferType : uint32_t {
  kVertex,
  kIndex,
};

enum class BufferUsage : uint32_t {
  kStatic,
  kDynamic,
};

enum class PixelFormat : uint32_t {
  kRGBA8888,
  kRGB888,
};

enum class ShaderStage : uint32_t {
  kVertex,
  kFragment,
};

enum class TextureCubeFace : uint32_t {
  kPositiveX = 0,
  kNegativeX = 1,
  kPositiveY = 2,
  kNegativeY = 3,
  kPositiveZ = 4,
  kNegativeZ = 5,
};

enum class TextureType : uint32_t {
  kTexture2D,
  kTextureCube,
};

enum class TextureUsage : uint32_t {
  kRead,
  kWrite,
  kRenderTarget,
};

enum class SamplerAddressMode : uint32_t {
  kRepeat,
  kMirroredRepeat,
  kClampToEdge,
};

enum class SamplerFilter : uint32_t {
  kLinear,
  kLinearMipmapLeaner,
  kLinearMipmapNearest,
  kNearest,
  kNearestMipmapLinear,
  kNearestMipmapNearst,
};

struct SamplerDescriptor {
  SamplerDescriptor& operator=(const SamplerDescriptor& other);

  bool operator==(const SamplerDescriptor& other) const;
  bool operator!=(const SamplerDescriptor& other) const;

  SamplerFilter mag_filter = SamplerFilter::kLinear;
  SamplerFilter min_filter = SamplerFilter::kLinear;

  SamplerAddressMode s_address_mode = SamplerAddressMode::kRepeat;
  SamplerAddressMode t_address_mode = SamplerAddressMode::kRepeat;
};

struct UniformInfo {
  int location[2] = { -1, -1 };

  ShaderStage stage = ShaderStage::kVertex;
  unsigned int type = 0;
  int count = 0;
  bool is_array = false;
  unsigned int size = 0;
};

struct AttributeInfo {
  int location = -1;

  unsigned int type = 0;
  int count = 0;
  unsigned int size = 0;
};

enum class VertexFormat : uint32_t {
  kFloat4,
  kFloat3,
  kFloat2,
  kFloat,
  kInt4,
  kInt3,
  kInt2,
  kInt,
  kUnsignedByte,
};

enum class PrimitiveType : uint32_t {
  kPoints,
  kLines,
  kLineLoop,
  kTriangles,
  kTriangleStrip,
};

enum class IndexFormat : uint32_t {
  kUnsignedShort,
  kUnsignedInt,
};

} // namespace gpu
} // namespace rezero

#endif // REZERO_GPU_TYPES_H_
