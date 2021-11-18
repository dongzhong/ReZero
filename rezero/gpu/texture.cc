// Created by Dong Zhong on 2021/11/16.

#include "rezero/gpu/texture.h"

namespace rezero {
namespace gpu {

TextureDescriptor::TextureDescriptor(const TextureDescriptor& other)
    : type(other.type),
      pixel_format(other.pixel_format),
      width(other.width),
      height(other.height) {}

TextureDescriptor& TextureDescriptor::operator=(const TextureDescriptor& other) {
  type = other.type;
  pixel_format = other.pixel_format;
  width = other.width;
  height = other.height;

  return *this;
}

#define byte(n) ((n) * 8)

static uint8_t ComputeBitsPerElements(PixelFormat format) {
  uint8_t result = 0;
  switch (format) {
    case PixelFormat::kRGBA8888:
      result = byte(4);
      break;
    case PixelFormat::kRGB888:
      result = byte(3);
      break;
    default:
      break;
  }
  return result;
}

#undef byte

Texture::Texture(const TextureDescriptor& descriptor)
    : pixel_format_(descriptor.pixel_format),
      width_(descriptor.width),
      height_(descriptor.height),
      bits_per_element_(ComputeBitsPerElements(descriptor.pixel_format)),
      type_(descriptor.type) {
  UpdateSamplerDescriptor(descriptor.sampler_descriptor);
}

Texture::~Texture() = default;

void Texture::UpdateSamplerDescriptor(const SamplerDescriptor& descriptor) {
  if (sampler_descriptor_ != descriptor) {
    sampler_descriptor_changed_ = true;
    sampler_descriptor_ = descriptor;
  }
}

Texture2D::Texture2D(const TextureDescriptor& descriptor)
    : Texture(descriptor) {}

Texture2D::~Texture2D() = default;

TextureCube::TextureCube(const TextureDescriptor& descriptor)
    : Texture(descriptor) {}

TextureCube::~TextureCube() = default;

} // namespace gpu
} // namespace rezero
