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

GLenum Utils::ToGLCompareFunction(CompareFunction compare_function) {
  auto res = GL_LESS;
  switch (compare_function) {
    case CompareFunction::kNever:
      res = GL_NEVER;
      break;
    case CompareFunction::kAlways:
      res = GL_ALWAYS;
      break;
    case CompareFunction::kEqual:
      res = GL_EQUAL;
      break;
    case CompareFunction::kNotEqual:
      res = GL_NOTEQUAL;
      break;
    case CompareFunction::kLess:
      res = GL_LESS;
      break;
    case CompareFunction::kLessEqual:
      res = GL_LEQUAL;
      break;
    case CompareFunction::kGreater:
      res = GL_GREATER;
      break;
    case CompareFunction::kGreaterEqual:
      res = GL_GEQUAL;
      break;
    default:
      break;
  }
  return res;
}

GLenum Utils::ToGLStencilOperation(StencilOperation stencil_operation) {
  auto res = GL_KEEP;
  switch (stencil_operation) {
    case StencilOperation::kZero:
      res = GL_ZERO;
      break;
    case StencilOperation::kKeep:
      res = GL_KEEP;
      break;
    case StencilOperation::kReplace:
      res = GL_REPLACE;
      break;
    case StencilOperation::kIncrementClamp:
      res = GL_INCR;
      break;
    case StencilOperation::kDecrementClamp:
      res = GL_DECR;
      break;
    case StencilOperation::kInvert:
      res = GL_INVERT;
      break;
    case StencilOperation::kIncrementWrap:
      res = GL_INCR_WRAP;
      break;
    case StencilOperation::kDecrementWrap:
      res = GL_DECR_WRAP;
      break;
    default:
      break;
  }
  return res;
}

void Utils::ToGLCullMode(CullMode cull_mode, bool& enable, GLenum& gl_cull_mode) {
  enable = static_cast<uint32_t>(cull_mode) != 0;
  auto front = static_cast<uint32_t>(cull_mode) & static_cast<uint32_t>(CullMode::kFront);
  auto back = static_cast<uint32_t>(cull_mode) & static_cast<uint32_t>(CullMode::kBack);
  if (front != 0 && back != 0) {
    gl_cull_mode = GL_FRONT_AND_BACK;
  } else if (back != 0) {
    gl_cull_mode = GL_BACK;
  } else {
    gl_cull_mode = GL_FRONT;
  }
}

GLenum Utils::ToGLWindingMode(WindingMode mode) {
  auto res = GL_CCW;
  switch (mode) {
    case WindingMode::kClockWise:
      res = GL_CW;
      break;
    case WindingMode::kCounterClockWise:
      res = GL_CCW;
      break;
    default:
      break;
  }
  return res;
}

GLenum Utils::ToGLPrimitiveType(PrimitiveType type) {
  auto res = GL_TRIANGLES;
  switch (type) {
    case PrimitiveType::kPoints:
      res = GL_POINTS;
      break;
    case PrimitiveType::kLines:
      res = GL_LINES;
      break;
    case PrimitiveType::kLineLoop:
      res = GL_LINE_LOOP;
      break;
    case PrimitiveType::kTriangles:
      res = GL_TRIANGLES;
      break;
    case PrimitiveType::kTriangleStrip:
      res = GL_TRIANGLE_STRIP;
      break;
    default:
      break;
  }
  return res;
}

GLenum Utils::ToGLIndexFormat(IndexFormat format) {
  auto res = GL_UNSIGNED_SHORT;
  switch (format) {
    case IndexFormat::kUnsignedShort:
      res = GL_UNSIGNED_SHORT;
      break;
    case IndexFormat::kUnsignedInt:
      res = GL_UNSIGNED_INT;
      break;
    default:
      break;
  }
  return res;
}

GLenum Utils::ToGLBlendOperation(BlendOperation blend_operation) {
  auto res = GL_FUNC_ADD;
  switch (blend_operation) {
    case BlendOperation::kAdd:
      res = GL_FUNC_ADD;
      break;
    case BlendOperation::kSubtract:
      res = GL_FUNC_SUBTRACT;
      break;
    case BlendOperation::kReverseSubtract:
      res = GL_FUNC_REVERSE_SUBTRACT;
      break;
    default:
      break;
  }
  return  res;
}

GLenum Utils::ToGLBlendFactor(BlendFactor blend_factor) {
  auto res = GL_ONE;
  switch (blend_factor) {
    case BlendFactor::kZero:
      res = GL_ZERO;
      break;
    case BlendFactor::kOne:
      res = GL_ONE;
      break;
    case BlendFactor::kSrcColor:
      res = GL_SRC_COLOR;
      break;
    case BlendFactor::kOneMinusSrcColor:
      res = GL_ONE_MINUS_SRC_COLOR;
      break;
    case BlendFactor::kDstColor:
      res = GL_DST_COLOR;
      break;
    case BlendFactor::kOneMinusDstColor:
      res = GL_ONE_MINUS_DST_COLOR;
      break;
    case BlendFactor::kSrcAlpha:
      res = GL_SRC_ALPHA;
      break;
    case BlendFactor::kOneMinusSrcAlpha:
      res = GL_ONE_MINUS_SRC_ALPHA;
      break;
    case BlendFactor::kDstAlpha:
      res = GL_DST_ALPHA;
      break;
    case BlendFactor::kOneMinusDstAlpha:
      res = GL_ONE_MINUS_DST_ALPHA;
      break;
    case BlendFactor::kConstantColor:
      res = GL_CONSTANT_COLOR;
      break;
    case BlendFactor::kOneMinusConstantColor:
      res = GL_ONE_MINUS_CONSTANT_COLOR;
      break;
    case BlendFactor::kConstantAlpha:
      res = GL_CONSTANT_ALPHA;
      break;
    case BlendFactor::kOneMinusConstantAlpha:
      res = GL_ONE_MINUS_CONSTANT_ALPHA;
      break;
    case BlendFactor::kSrcAlphaSaturate:
      res = GL_SRC_ALPHA_SATURATE;
      break;
    default:
      break;
  }
  return res;
}

GLenum Utils::ToGLAttributeType(VertexFormat format) {
  GLenum res = GL_INT;

  switch (format) {
    case VertexFormat::kFloat4:
    case VertexFormat::kFloat3:
    case VertexFormat::kFloat2:
    case VertexFormat::kFloat:
      res = GL_FLOAT;
      break;
    case VertexFormat::kInt4:
    case VertexFormat::kInt3:
    case VertexFormat::kInt2:
    case VertexFormat::kInt:
      res = GL_INT;
      break;
    case VertexFormat::kUnsignedByte4:
      res = GL_UNSIGNED_BYTE;
      break;
    default:
      break;
  }

  return res;
}

GLsizei Utils::GetAttributeSize(VertexFormat format) {
  GLsizei res = 0;

  switch (format) {
    case VertexFormat::kFloat4:
    case VertexFormat::kInt4:
    case VertexFormat::kUnsignedByte4:
      res = 4;
      break;
    case VertexFormat::kFloat3:
    case VertexFormat::kInt3:
      res = 3;
      break;
    case VertexFormat::kFloat2:
    case VertexFormat::kInt2:
      res = 2;
      break;
    case VertexFormat::kFloat:
    case VertexFormat::kInt:
      res = 1;
      break;
    default:
      break;
  }

  return res;
}

} // namespace gpu
} // namespace rezero
