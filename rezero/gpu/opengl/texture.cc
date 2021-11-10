// Created by Dong Zhong on 2021/10/28.

#include "rezero/gpu/texture.h"

#include "rezero/base/logging.h"
#include "rezero/gpu/opengl/state_machine_gl.h"

namespace rezero {
namespace gpu {

namespace opengl {

void TextureGL::ApplySamplers() {
  if (sampler_has_changed) {
    glTexParameteri(texture_type_, GL_TEXTURE_MAG_FILTER, mag_filter);
    glTexParameteri(texture_type_, GL_TEXTURE_MIN_FILTER, min_filter);
    glTexParameteri(texture_type_, GL_TEXTURE_WRAP_S, s_wrap_mode);
    glTexParameteri(texture_type_, GL_TEXTURE_WRAP_T, t_wrap_mode);
    sampler_has_changed = false;
  }
}

} // namespace opengl

#define byte(n) ((n) * 8)

uint8_t ComputeBitsPerElements(PixelFormat format) {
  auto result = 0;
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
    : width_(descriptor.width_),
      height_(descriptor.height_),
      bits_per_element_(ComputeBitsPerElements(descriptor.pixel_format_)),
      has_mipmap_(false),
      texture_type_(descriptor.texture_type_),
      texture_usage_(descriptor.texture_usage_),
      pixel_format_(descriptor.pixel_format_) {
  glGenTextures(1, &texture_.texture_name_);
  REZERO_DCHECK(texture_.texture_name_ > 0);

  UpdateTextureDescriptor(descriptor);
}

Texture::~Texture() {
  if (texture_.texture_name_ > 0) {
    auto& state_machine = StateMachineGL::GetCurrent();
    state_machine.UnbindTextureForAllUnit(texture_.texture_type_, texture_.texture_name_);
    glDeleteBuffers(1, &texture_.texture_name_);
    texture_.texture_name_ = 0;
  }
}

void Texture::UpdateSamplerDescriptor(const SamplerDescriptor& descripotr) {
  texture_.sampler_has_changed = (sampler_descriptor_ != descripotr);
  sampler_descriptor_ = descripotr;

  texture_.mag_filter = Utils::ToGLMagSamplerFilter(sampler_descriptor_.mag_filter);
  texture_.min_filter = Utils::ToGLMinSamplerFilter(sampler_descriptor_.min_filter);
  texture_.s_wrap_mode = Utils::ToGLSamplerAddressMode(sampler_descriptor_.s_address_mode);
  texture_.t_wrap_mode = Utils::ToGLSamplerAddressMode(sampler_descriptor_.t_address_mode);
}

void Texture::GenerateMipmap() {
  if (texture_usage_ == TextureUsage::kRenderTarget) {
    return;
  }

  if (!has_mipmap_) {
    Apply(0);

    glGenerateMipmap(texture_.texture_type_);
    has_mipmap_ = true;
  }
}

void Texture::Apply(int unit) {
  auto& state_machine = StateMachineGL::GetCurrent();
  state_machine.BindTexture(unit, texture_.texture_type_, texture_.texture_name_);

  texture_.ApplySamplers();
}

void Texture::UpdateTextureDescriptor(const TextureDescriptor& descriptor) {
  texture_.texture_type_ = Utils::ToGLTextureType(descriptor.texture_type_);
  Utils::ToGLTypes(descriptor.pixel_format_,
                   texture_.internal_format_,
                   texture_.format_,
                   texture_.data_type_);

  UpdateSamplerDescriptor(descriptor.sampler_descriptor);
  texture_.sampler_has_changed = true;
}

Texture2D::Texture2D(const TextureDescriptor& descriptor)
    : Texture(descriptor) {
  InitWithZeros();
}

Texture2D::~Texture2D() {}

void Texture2D::UpdateData(const void* data,
                           uint32_t width,
                           uint32_t height,
                           int level) {
  Apply(0);

  width_ = width;
  height_ = height;
  glTexImage2D(texture_.texture_type_,
               static_cast<GLint>(level),
               texture_.internal_format_,
               static_cast<GLsizei>(width),
               static_cast<GLsizei>(height),
               0,
               texture_.format_,
               texture_.data_type_,
               static_cast<const GLvoid*>(data));
  CHECK_GL_ERROR_DEBUG();

  if (!has_mipmap_ && level > 0) {
    has_mipmap_ = true;
  } else {
    has_mipmap_ = false;
  }
}

void Texture2D::UpdateSubData(const void* data,
                              int32_t x_offset,
                              int32_t y_offset,
                              uint32_t width,
                              uint32_t height,
                              int level) {
  Apply(0);

  glTexSubImage2D(texture_.texture_type_,
                  static_cast<GLint>(level),
                  static_cast<GLint>(x_offset),
                  static_cast<GLint>(y_offset),
                  static_cast<GLsizei>(width),
                  static_cast<GLsizei>(height),
                  texture_.format_,
                  texture_.data_type_,
                  static_cast<const GLvoid*>(data));
  CHECK_GL_ERROR_DEBUG();

  if (!has_mipmap_ && level > 0) {
    has_mipmap_ = true;
  } else {
    has_mipmap_ = false;
  }
}

void Texture2D::InitWithZeros() {
  auto size = width_ * height_ * bits_per_element_;
  std::unique_ptr<char[]> data = std::make_unique<char[]>(size);
  memset(data.get(), 0, size);
  UpdateData(data.get(), width_, height_, 0);
}

TextureCube::TextureCube(const TextureDescriptor& descriptor)
    : Texture(descriptor) {
  REZERO_DCHECK(width_ == height_);
}

TextureCube::~TextureCube() {}

void TextureCube::UpdateFaceData(TextureCubeFace side, const void* data) {
  Apply(0);

  int face_side = static_cast<int>(side);
  glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + face_side,
               0,
               texture_.internal_format_,
               static_cast<GLsizei>(width_),
               static_cast<GLsizei>(height_),
               0,
               texture_.format_,
               texture_.data_type_,
               static_cast<const GLvoid*>(data));
  CHECK_GL_ERROR_DEBUG();
}

} // namespace gpu
} // namespace rezero
