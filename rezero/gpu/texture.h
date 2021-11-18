// Created by Dong Zhong on 2021/11/16.

#ifndef REZERO_GPU_TEXTURE_H_
#define REZERO_GPU_TEXTURE_H_

#include "rezero/base/macros.h"
#include "rezero/gpu/enums.h"
#include "rezero/gpu/types.h"

namespace rezero {
namespace gpu {

struct TextureDescriptor {
  TextureDescriptor() = default;
  TextureDescriptor(const TextureDescriptor& other);

  TextureDescriptor& operator=(const TextureDescriptor& other);

  TextureType type = TextureType::kTexture2D;
  PixelFormat pixel_format = PixelFormat::kRGBA8888;
  uint32_t width = 0;
  uint32_t height = 0;

  SamplerDescriptor sampler_descriptor;
};

class Texture {
 public:
  Texture(const TextureDescriptor& descriptor);
  virtual ~Texture();

  void UpdateSamplerDescriptor(const SamplerDescriptor& descriptor);

  virtual void GenerateMipmap() = 0;

  virtual void Apply(int unit) = 0;

 protected:
  PixelFormat pixel_format_ = PixelFormat::kRGBA8888;
  uint32_t width_ = 0;
  uint32_t height_ = 0;
  uint8_t bits_per_element_ = 0;

  SamplerDescriptor sampler_descriptor_;
  bool sampler_descriptor_changed_ = true;

  bool has_mipmap_ = false;

 private:
  TextureType type_ = TextureType::kTexture2D;

  REZERO_DISALLOW_COPY_AND_ASSIGN(Texture);
};

class Texture2D : public Texture {
 public:
  Texture2D(const TextureDescriptor& descriptor);
  ~Texture2D() override;

  virtual void UpdateData(const void* data,
                          uint32_t width,
                          uint32_t height,
                          int level) = 0;

  virtual void UpdateSubData(const void* data,
                             int32_t x_offset,
                             int32_t y_offset,
                             uint32_t width,
                             uint32_t height,
                             int level) = 0;

 private:
  REZERO_DISALLOW_COPY_AND_ASSIGN(Texture2D);
};

class TextureCube : public Texture {
 public:
  TextureCube(const TextureDescriptor& descriptor);
  ~TextureCube() override;

  virtual void UpdateFaceData(TextureCubeFace side, const void* data) = 0;

 private:
  REZERO_DISALLOW_COPY_AND_ASSIGN(TextureCube);
};

} // namespace gpu
} // namespace rezero

#endif // REZERO_GPU_TEXTURE_H_
