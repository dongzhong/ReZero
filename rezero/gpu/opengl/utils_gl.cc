// Created by Dong Zhong on 2021/11/16.

#include "rezero/gpu/opengl/utils_gl.h"

namespace rezero {
namespace gpu {

UtilsGL::UtilsGL() = default;

UtilsGL::~UtilsGL() = default;

GLenum UtilsGL::ToGLBufferType(BufferType type) {
  GLenum res = GL_ARRAY_BUFFER;
  switch (type) {
    case BufferType::kVertex:
      res = GL_ARRAY_BUFFER;
      break;
    case BufferType::kIndex:
      res = GL_ELEMENT_ARRAY_BUFFER;
      break;
    default:
      break;
  }
  return res;
}

GLenum UtilsGL::ToGLBufferUsage(BufferUsage usage) {
  GLenum res = GL_STATIC_DRAW;
  switch (usage) {
    case BufferUsage::kStatic:
      res = GL_STATIC_DRAW;
      break;
    case BufferUsage::kDynamic:
      res = GL_DYNAMIC_DRAW;
      break;
    default:
      break;
  }
  return res;
}

} // namespace gpu
} // namespace rezero
