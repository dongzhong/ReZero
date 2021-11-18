// Created by Dong Zhong on 2021/11/16.

#ifndef REZERO_GPU_OPENGL_TEXTURE_GL_H_
#define REZERO_GPU_OPENGL_TEXTURE_GL_H_

#include "rezero/gpu/texture.h"
#include "rezero/gpu/opengl/includes_gl.h"

namespace rezero {
namespace gpu {

class Texture2DGL final : public Texture2D {
 public:
  Texture2DGL(const TextureDescriptor& descriptor);
  ~Texture2DGL() override;

  // Texture
  void GenerateMipmap() override;

  // Texture
  void Apply(int unit) override;

  // Texture2D
  void UpdateData(const void* data,
                  uint32_t width,
                  uint32_t height,
                  int level) override;

  // Texture2D
  void UpdateSubData(const void* data,
                     int32_t x_offset,
                     int32_t y_offset,
                     uint32_t width,
                     uint32_t height,
                     int level) override;

  GLuint GetTextureName() const { return texture_name_; }

 private:
  void ApplySampderDescriptor();

  void InitWithZero();

  GLuint texture_name_ = 0;
  GLint internal_format_ = GL_RGBA;
  GLenum format_ = GL_RGBA;
  GLenum data_type_ = GL_UNSIGNED_BYTE;

  REZERO_DISALLOW_COPY_AND_ASSIGN(Texture2DGL);
};

class TextureCubeGL final : public TextureCube {
 public:
  TextureCubeGL(const TextureDescriptor& descriptor);
  ~TextureCubeGL() override;

  // Texture
  void GenerateMipmap() override;

  // Texture
  void Apply(int unit) override;

  // TextureCube
  void UpdateFaceData(TextureCubeFace side, const void* data) override;

  GLuint GetTextureName() const { return texture_name_; }

 private:
  void ApplySampderDescriptor();

  GLuint texture_name_ = 0;
  GLint internal_format_ = GL_RGBA;
  GLenum format_ = GL_RGBA;
  GLenum data_type_ = GL_UNSIGNED_BYTE;

  REZERO_DISALLOW_COPY_AND_ASSIGN(TextureCubeGL);
};

} // namespace gpu
} // namespace rezero

#endif // REZERO_GPU_OPENGL_TEXTURE_GL_H_
