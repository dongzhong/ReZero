// Created by Dong Zhong on 2021/11/16.

#include "rezero/gpu/opengl/texture_gl.h"

#include "rezero/base/logging.h"
#include "rezero/gpu/opengl/state_machine_gl.h"
#include "rezero/gpu/opengl/utils_gl.h"

namespace rezero {
namespace gpu {

Texture2DGL::Texture2DGL(const TextureDescriptor& descriptor)
    : Texture2D(descriptor) {
  glGenTextures(1, &texture_name_);
  REZERO_DCHECK(texture_name_ > 0);
  UtilsGL::ToGLTypes(pixel_format_, internal_format_, format_, data_type_);

  InitWithZero();
}

Texture2DGL::~Texture2DGL() {
  if (texture_name_ > 0) {
    auto& state_machine = StateMachineGL::GetCurrent();
    state_machine.UnbindBuffer(GL_TEXTURE_2D, texture_name_);
    glDeleteTextures(1, &texture_name_);
    texture_name_ = 0;
  }
}

void Texture2DGL::GenerateMipmap() {
  if (!has_mipmap_) {
    Apply(0);

    glGenerateMipmap(GL_TEXTURE_2D);
    has_mipmap_ = true;
  }
}

void Texture2DGL::Apply(int unit) {
  auto& state_machine = StateMachineGL::GetCurrent();
  state_machine.BindTexture(unit, GL_TEXTURE_2D, texture_name_);
  ApplySampderDescriptor();
}

void Texture2DGL::UpdateData(const void* data,
                             uint32_t width,
                             uint32_t height,
                             int level) {
  Apply(0);
  width_ = width;
  height_ = height;
  glTexImage2D(GL_TEXTURE_2D,
               static_cast<GLint>(level),
               internal_format_,
               static_cast<GLsizei>(width_),
               static_cast<GLsizei>(height),
               0,
               format_,
               data_type_,
               static_cast<const GLvoid*>(data));
  REZERO_DCHECK_GL_ERROR();

  if (!has_mipmap_ && level > 0) {
    has_mipmap_ = true;
  } else {
    has_mipmap_ = false;
  }
}

void Texture2DGL::UpdateSubData(const void* data,
                                int32_t x_offset,
                                int32_t y_offset,
                                uint32_t width,
                                uint32_t height,
                                int level) {
  Apply(0);
  glTexSubImage2D(GL_TEXTURE_2D,
                  static_cast<GLint>(level),
                  static_cast<GLint>(x_offset),
                  static_cast<GLint>(y_offset),
                  static_cast<GLsizei>(width),
                  static_cast<GLsizei>(height),
                  format_,
                  data_type_,
                  static_cast<const GLvoid*>(data));
  REZERO_DCHECK_GL_ERROR();

  if (!has_mipmap_ && level > 0) {
    has_mipmap_ = true;
  } else {
    has_mipmap_ = false;
  }
}

void Texture2DGL::ApplySampderDescriptor() {
  if (sampler_descriptor_changed_) {
    sampler_descriptor_changed_ = false;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
                    UtilsGL::ToGLMagSamplerFilter(sampler_descriptor_.mag_filter));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    UtilsGL::ToGLMinSamplerFilter(sampler_descriptor_.min_filter));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                    UtilsGL::ToGLSamplerAddressMode(sampler_descriptor_.s_address_mode));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
                    UtilsGL::ToGLSamplerAddressMode(sampler_descriptor_.t_address_mode));
  }
}

void Texture2DGL::InitWithZero() {
  std::size_t size = width_ * height_ * bits_per_element_ / 8;
  std::unique_ptr<char[]> data = std::make_unique<char[]>(size);
  memset(data.get(), 0x00, size);
  UpdateData(data.get(), width_, height_, 0);
}

TextureCubeGL::TextureCubeGL(const TextureDescriptor& descriptor)
    : TextureCube(descriptor) {
  glGenTextures(1, &texture_name_);
  REZERO_DCHECK(texture_name_ > 0);
  UtilsGL::ToGLTypes(pixel_format_, internal_format_, format_, data_type_);
}

TextureCubeGL::~TextureCubeGL() {
  if (texture_name_ > 0) {
    auto& state_machine = StateMachineGL::GetCurrent();
    state_machine.UnbindBuffer(GL_TEXTURE_CUBE_MAP, texture_name_);
    glDeleteTextures(1, &texture_name_);
    texture_name_ = 0;
  }
}

void TextureCubeGL::GenerateMipmap() {
  if (!has_mipmap_) {
    Apply(0);

    glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
    has_mipmap_ = true;
  }
}

void TextureCubeGL::Apply(int unit) {
  auto& state_machine = StateMachineGL::GetCurrent();
  state_machine.BindTexture(unit, GL_TEXTURE_CUBE_MAP, texture_name_);
  ApplySampderDescriptor();
}

void TextureCubeGL::UpdateFaceData(TextureCubeFace side, const void* data) {
  Apply(0);

  int face_side = static_cast<int>(side);
  glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + face_side,
               0,
               internal_format_,
               static_cast<GLsizei>(width_),
               static_cast<GLsizei>(height_),
               0,
               format_,
               data_type_,
               static_cast<const GLvoid*>(data));
  REZERO_DCHECK_GL_ERROR();
}

void TextureCubeGL::ApplySampderDescriptor() {
  if (sampler_descriptor_changed_) {
    sampler_descriptor_changed_ = false;
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER,
                    UtilsGL::ToGLMagSamplerFilter(sampler_descriptor_.mag_filter));
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER,
                    UtilsGL::ToGLMinSamplerFilter(sampler_descriptor_.min_filter));
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S,
                    UtilsGL::ToGLSamplerAddressMode(sampler_descriptor_.s_address_mode));
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T,
                    UtilsGL::ToGLSamplerAddressMode(sampler_descriptor_.t_address_mode));
  }
}

} // namespace gpu
} // namespace rezero
