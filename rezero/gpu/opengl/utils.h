// Created by Dong Zhong on 2021/10/29.

#ifndef REZERO_GPU_OPENGL_UTILS_H_
#define REZERO_GPU_OPENGL_UTILS_H_

#include "rezero/base/macros.h"
#include "rezero/gpu/opengl/includes.h"
#include "rezero/gpu/types.h"

namespace rezero {
namespace gpu {

// TODO:
#define CHECK_GL_ERROR()

#define CHECK_GL_ERROR_DEBUG()

class Utils {
 public:
  static GLenum ToGLBufferType(BufferType type);

  static GLenum ToGLBufferUsage(BufferUsage usage);

  static GLenum ToGLTextureType(TextureType type);

  static void ToGLTypes(PixelFormat pixel_format, GLint& internal_format, GLenum& format, GLenum& type);

  static GLenum ToGLMagSamplerFilter(SamplerFilter sampler_filter);

  static GLenum ToGLMinSamplerFilter(SamplerFilter sampler_filter);

  static GLenum ToGLSamplerAddressMode(SamplerAddressMode sampler_address_mode);

 private:
  REZERO_DISALLOW_IMPLICIT_CONSTRUCTORS(Utils);
};

const static int kMaxTextureUnits = 8;

} // namespace gpu
} // namespace rezero

#endif // REZERO_GPU_OPENGL_UTILS_H_