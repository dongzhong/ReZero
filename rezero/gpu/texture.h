// Created by Dong Zhong on 2021/10/28.

#ifndef REZERO_GPU_TEXTURE_H_
#define REZERO_GPU_TEXTURE_H_

#include <cstddef>

#include "rezero/gpu/defines.h"
#include REZERO_GPU_BACKEND(texture.h)

namespace rezero {
namespace gpu {

struct TextureDescriptor {
  TextureType texture_type_ = TextureType::kTexture2D;
  TextureUsage texture_usage_ = TextureUsage::kRead;
  PixelFormat pixel_format_ = PixelFormat::kRGBA8888;
  uint32_t width_ = 0;
  uint32_t height_ = 0;
  uint32_t depth_ = 0;

  SamplerDescriptor sampler_descriptor;
};

class Texture {
 public:
  using InternalTexture = ImplType<Texture>::type;

  Texture(const TextureDescriptor& descriptor);
  virtual ~Texture();

  void UpdateSamplerDescriptor(const SamplerDescriptor& descripotr);

  void GenerateMipmap();

  void Apply(int unit);

  const InternalTexture& GetInteralTexture() { return texture_; }

 protected:
  void UpdateTextureDescriptor(const TextureDescriptor& descriptor);

  InternalTexture texture_;

  uint32_t width_ = 0;
  uint32_t height_ = 0;
  uint8_t bits_per_element_ = 0;
  bool has_mipmap_ = false;

  TextureType texture_type_ = TextureType::kTexture2D;
  TextureUsage texture_usage_ = TextureUsage::kRead;
  PixelFormat pixel_format_ = PixelFormat::kRGBA8888;

  SamplerDescriptor sampler_descriptor_;

  REZERO_DISALLOW_COPY_AND_ASSIGN(Texture);
};

class Texture2D final : public Texture {
 public:
  Texture2D(const TextureDescriptor& descriptor);
  ~Texture2D() override;

  void UpdateData(const void* data, uint32_t width, uint32_t height, int level);

  void UpdateSubData(const void* data, int32_t x_offset, int32_t y_offset,
                     uint32_t width, uint32_t height, int level);

  uint32_t GetWidth() const { return width_; }

  uint32_t GetHeith() const { return height_; }

 private:
  void InitWithZeros();

  REZERO_DISALLOW_COPY_AND_ASSIGN(Texture2D);
};

class TextureCube final : public Texture {
 public:
  TextureCube(const TextureDescriptor& descriptor);
  ~TextureCube() override;

  void UpdateFaceData(TextureCubeFace side, const void* data);

 private:
  REZERO_DISALLOW_COPY_AND_ASSIGN(TextureCube);
};

} // namespace gpu
} // namespace rezero

#endif // REZERO_GPU_TEXTURE_H_
