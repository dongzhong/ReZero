// Created by Dong Zhong on 2021/11/16.

#ifndef REZERO_GPU_OPENGL_UTILS_GL_H_
#define REZERO_GPU_OPENGL_UTILS_GL_H_

#include <cstddef>

#include "rezero/base/macros.h"
#include "rezero/gpu/enums.h"
#include "rezero/gpu/opengl/includes_gl.h"

namespace rezero {
namespace gpu {

#define REZERO_CHECK_GL_ERROR() \


#define REZERO_DCHECK_GL_ERROR() \


class UtilsGL final {
 public:
  static GLenum ToGLBufferType(BufferType type);

  static GLenum ToGLBufferUsage(BufferUsage usage);

  static GLenum ToGLShaderStage(ShaderStage stage);

  static std::size_t GetGLDataTypeSize(GLenum type);

  static GLenum ToGLMagSamplerFilter(SamplerFilter filter);

  static GLenum ToGLMinSamplerFilter(SamplerFilter filter);

  static GLenum ToGLSamplerAddressMode(SamplerAddressMode mode);

  static void ToGLTypes(PixelFormat pixel_format,
                        GLint& internal_format,
                        GLenum& format,
                        GLenum& type);

 private:
  UtilsGL();
  ~UtilsGL();

  REZERO_DISALLOW_COPY_ASSIGN_AND_MOVE(UtilsGL);
};

} // namespace gpu
} // namespace rezero

#endif // REZERO_GPU_OPENGL_UTILS_GL_H_