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

GLsizei Utils::GetGLDataTypeSize(GLenum type) {
  GLsizei size = 0;
  switch (type) {
    case GL_BOOL:
    case GL_BYTE:
    case GL_UNSIGNED_BYTE:
      size = sizeof(GLbyte);
      break;
    case GL_BOOL_VEC2:
    case GL_SHORT:
    case GL_UNSIGNED_SHORT:
      size = sizeof(GLshort);
      break;
    case GL_BOOL_VEC3:
      size = sizeof(GLbyte) * 3;
      break;
    case GL_BOOL_VEC4:
    case GL_INT:
    case GL_UNSIGNED_INT:
    case GL_FLOAT:
      size = sizeof(GLfloat);
      break;
    case GL_FLOAT_VEC2:
    case GL_INT_VEC2:
      size = sizeof(GLfloat) * 2;
      break;
    case GL_FLOAT_VEC3:
    case GL_INT_VEC3:
      size = sizeof(GLfloat) * 3;
      break;
    case GL_FLOAT_VEC4:
    case GL_INT_VEC4:
    case GL_FLOAT_MAT2:
      size = sizeof(GLfloat) * 4;
      break;
    case GL_FLOAT_MAT3:
      size = sizeof(GLfloat) * 9;
      break;
    case GL_FLOAT_MAT4:
      size = sizeof(GLfloat) * 16;
      break;
    default:
      break;
  }
  return size;
}

GLenum Utils::ToGLShaderStage(ShaderStage stage) {
  auto result = GL_VERTEX_SHADER;
  switch (stage) {
    case ShaderStage::kVertex:
      result = GL_VERTEX_SHADER;
      break;
    case ShaderStage::kFragment:
      result = GL_FRAGMENT_SHADER;
      break;
    default:
      break;
  }
  return result;
}

GLenum Utils::ToGLTextureType(TextureType type) {
  auto result = GL_TEXTURE_2D;
  switch (type) {
    case TextureType::kTexture2D:
      result = GL_TEXTURE_2D;
      break;
    case TextureType::kTextureCube:
      result = GL_TEXTURE_CUBE_MAP;
      break;
    default:
      break;
  }
  return result;
}

void Utils::ToGLTypes(PixelFormat pixel_format,
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

GLenum Utils::ToGLMagSamplerFilter(SamplerFilter sampler_filter) {
  auto result = GL_LINEAR;
  switch (sampler_filter) {
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

GLenum Utils::ToGLMinSamplerFilter(SamplerFilter sampler_filter) {
  auto result = GL_LINEAR;
  switch (sampler_filter) {
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

GLenum Utils::ToGLSamplerAddressMode(SamplerAddressMode sampler_address_mode) {
  auto result = GL_REPEAT;
  switch (sampler_address_mode) {
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

} // namespace gpu
} // namespace rezero
