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

enum class BlendOperation : uint32_t {
  kAdd,
  kSubtract,
  kReverseSubtract,
};

enum class BlendFactor : uint32_t {
  kZero,
  kOne,
  kSrcColor,
  kOneMinusSrcColor,
  kDstColor,
  kOneMinusDstColor,
  kSrcAlpha,
  kOneMinusSrcAlpha,
  kDstAlpha,
  kOneMinusDstAlpha,
  kConstantColor,
  kOneMinusConstantColor,
  kConstantAlpha,
  kOneMinusConstantAlpha,
  kSrcAlphaSaturate,
};

enum class ColorWriteMask : uint32_t {
  kNone = 0x00000000,
  kRed = 0x00000001,
  kGreen = 0x00000002,
  kBlue = 0x00000004,
  kAlpha = 0x00000008,
  kAll = 0x0000000F,
};

struct BlendDescriptor {
  BlendDescriptor() = default;

  BlendDescriptor(const BlendDescriptor& other);

  BlendDescriptor& operator=(const BlendDescriptor& other);

  bool blend_enable = false;

  BlendOperation alpha_blend_operation = BlendOperation::kAdd;
  BlendOperation rgb_blend_operation = BlendOperation::kAdd;

  BlendFactor src_alpha_blend_factor = BlendFactor::kOne;
  BlendFactor src_rgb_blend_factor = BlendFactor::kOne;
  BlendFactor dst_alpha_blend_factor = BlendFactor::kZero;
  BlendFactor dst_rgb_blend_factor = BlendFactor::kZero;

  uint32_t color_mask = 0x0000000F;
};

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
  kUnsignedByte4,
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

enum class CompareFunction : uint32_t {
  kNever,
  kAlways,
  kEqual,
  kNotEqual,
  kLess,
  kLessEqual,
  kGreater,
  kGreaterEqual,
};

enum class StencilOperation : uint32_t {
  kZero,
  kKeep,
  kReplace,
  kIncrementClamp,
  kDecrementClamp,
  kInvert,
  kIncrementWrap,
  kDecrementWrap,
};

struct Region {
  Region() = default;

  Region(int x_, int y_, unsigned int width_, unsigned int height_)
      : x(x_), y(y_), width(width_), height(height_) {}

  Region& operator=(const Region& other) {
    x = other.x;
    y = other.y;
    width = other.width;
    height = other.height;

    return *this;
  }

  bool operator==(const Region& other) const {
    return (x == other.x) &&
           (y == other.y) &&
           (width == other.width) &&
           (height == other.height);
  }

  bool operator!=(const Region& other) const {
    return !operator==(other);
  }

  int x = 0;
  int y = 0;
  unsigned int width = 0;
  unsigned int height = 0;
};

enum class CullMode : uint32_t {
  kNone = 0x00000000,
  kFront = 0x00000001,
  kBack = 0x00000002,
};

enum class WindingMode : uint32_t {
  kClockWise,
  kCounterClockWise,
};

} // namespace gpu
} // namespace rezero

#endif // REZERO_GPU_TYPES_H_
