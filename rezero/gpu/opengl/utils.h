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

 private:
  REZERO_DISALLOW_IMPLICIT_CONSTRUCTORS(Utils);
};

} // namespace gpu
} // namespace rezero

#endif // REZERO_GPU_OPENGL_UTILS_H_
