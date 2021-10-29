// Created by Dong Zhong on 2021/10/29.

#include "rezero/gpu/opengl/utils.h"

namespace rezero {
namespace gpu {

GLenum Utils::ToGLBufferType(BufferType type) {
  auto result = GL_ARRAY_BUFFER;
  switch (type) {
    case BufferType::kVertex:
      result = GL_ARRAY_BUFFER;
      break;
    case BufferType::kIndex:
      result = GL_ELEMENT_ARRAY_BUFFER;
      break;
    default:
      break;
  }
  return result;
}

GLenum Utils::ToGLBufferUsage(BufferUsage usage) {
  auto result = GL_STATIC_DRAW;
  switch (usage) {
    case BufferUsage::kStatic:
      result = GL_STATIC_DRAW;
      break;
    case BufferUsage::kDynamic:
      result = GL_DYNAMIC_DRAW;
      break;
    default:
      break;
  }
  return result;
}

} // namespace gpu
} // namespace rezero
