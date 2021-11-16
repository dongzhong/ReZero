// Created by Dong Zhong on 2021/11/16.

#ifndef REZERO_GPU_OPENGL_SHADER_GL_H_
#define REZERO_GPU_OPENGL_SHADER_GL_H_

#include "rezero/gpu/opengl/includes_gl.h"
#include "rezero/gpu/shader.h"

namespace rezero {
namespace gpu {

class ShaderGL final : public Shader {
 public:
  ShaderGL(ShaderStage stage, const std::string& source);
  virtual ~ShaderGL();

  GLenum GetShaderStage() const { return shader_stage_; }

  GLuint GetShaderName() const { return shader_name_; }

 private:
  void DeleteShader();

  GLenum shader_stage_ = GL_VERTEX_SHADER;
  GLuint shader_name_;

  REZERO_DISALLOW_COPY_AND_ASSIGN(ShaderGL);
};

} // namespace gpu
} // namespace rezero

#endif // REZERO_GPU_OPENGL_SHADER_GL_H_
