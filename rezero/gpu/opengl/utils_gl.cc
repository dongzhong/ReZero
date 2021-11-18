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

GLenum UtilsGL::ToGLShaderStage(ShaderStage stage) {
  GLenum res = GL_VERTEX_SHADER;
  switch (stage) {
    case ShaderStage::kVertex:
      res = GL_VERTEX_SHADER;
      break;
    case ShaderStage::kFragment:
      res = GL_FRAGMENT_SHADER;
      break;
    default:
      break;
  }
  return res;
}

std::size_t UtilsGL::GetGLDataTypeSize(GLenum type) {
  std::size_t res = 0;
  switch (type) {
    case GL_BOOL:
      res = sizeof(GLboolean);
      break;
    case GL_BOOL_VEC2:
      res = sizeof(GLboolean) * 2;
      break;
    case GL_BOOL_VEC3:
      res = sizeof(GLboolean) * 3;
      break;
    case GL_FLOAT:
    case GL_INT:
    case GL_BOOL_VEC4:
      res = sizeof(GLfloat);
      break;
    case GL_FLOAT_VEC2:
    case GL_INT_VEC2:
      res = sizeof(GLfloat) * 2;
      break;
    case GL_FLOAT_VEC3:
    case GL_INT_VEC3:
      res = sizeof(GLfloat) * 3;
      break;
    case GL_FLOAT_VEC4:
    case GL_INT_VEC4:
    case GL_FLOAT_MAT2:
      res = sizeof(GLfloat) * 4;
      break;
    case GL_FLOAT_MAT3:
      res = sizeof(GLfloat) * 9;
      break;
    case GL_FLOAT_MAT4:
      res = sizeof(GLfloat) * 16;
      break;
    case GL_SAMPLER_2D:
    case GL_SAMPLER_CUBE:
      res = 0;
      break;
    default:
      break;
  }
  return res;
}

GLenum UtilsGL::ToGLMagSamplerFilter(SamplerFilter filter) {
  GLenum result = GL_LINEAR;
  switch (filter) {
    case SamplerFilter::kLinear:
    case SamplerFilter::kLinearMipmapLeaner:
    case SamplerFilter::kLinearMipmapNearest:
      result = GL_LINEAR;
      break;
    case SamplerFilter::kNearest:
    case SamplerFilter::kNearestMipmapLinear:
    case SamplerFilter::kNearestMipmapNearst:
      result = GL_NEAREST;
      break;
    default:
      break;
  }
  return result;
}

GLenum UtilsGL::ToGLMinSamplerFilter(SamplerFilter filter) {
  GLenum result = GL_LINEAR;
  switch (filter) {
    case SamplerFilter::kLinear:
      result = GL_LINEAR;
      break;
    case SamplerFilter::kLinearMipmapLeaner:
      result = GL_LINEAR_MIPMAP_LINEAR;
      break;
    case SamplerFilter::kLinearMipmapNearest:
      result = GL_LINEAR_MIPMAP_LINEAR;
      break;
    case SamplerFilter::kNearest:
      result = GL_NEAREST;
      break;
    case SamplerFilter::kNearestMipmapLinear:
      result = GL_NEAREST_MIPMAP_LINEAR;
      break;
    case SamplerFilter::kNearestMipmapNearst:
      result = GL_NEAREST_MIPMAP_NEAREST;
      break;
    default:
      break;
  }
  return result;
}

GLenum UtilsGL::ToGLSamplerAddressMode(SamplerAddressMode mode) {
  GLenum result = GL_REPEAT;
  switch (mode) {
    case SamplerAddressMode::kRepeat:
      result = GL_REPEAT;
      break;
    case SamplerAddressMode::kMirroredRepeat:
      result = GL_MIRRORED_REPEAT;
      break;
    case SamplerAddressMode::kClampToEdge:
      result = GL_CLAMP_TO_EDGE;
      break;
    default:
      break;
  }
  return result;
}

void UtilsGL::ToGLTypes(PixelFormat pixel_format,
                        GLint& internal_format,
                        GLenum& format,
                        GLenum& type) {
  switch (pixel_format) {
    case PixelFormat::kRGBA8888:
      internal_format = GL_RGBA;
      format = GL_RGBA;
      type = GL_UNSIGNED_BYTE;
      break;
    case PixelFormat::kRGB888:
      internal_format = GL_RGB;
      format = GL_RGB;
      type = GL_UNSIGNED_BYTE;
      break;
    default:
      break;
  }
}

} // namespace gpu
} // namespace rezero
