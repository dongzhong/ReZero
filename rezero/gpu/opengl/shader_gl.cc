// Created by Dong Zhong on 2021/11/16.

#include "rezero/gpu/opengl/shader_gl.h"

#include "rezero/base/logging.h"
#include "rezero/gpu/opengl/utils_gl.h"

namespace rezero {
namespace gpu {

ShaderGL::ShaderGL(ShaderStage stage, const std::string& source)
    : Shader(stage, source),
      shader_stage_(UtilsGL::ToGLShaderStage(stage)) {
  shader_name_ = glCreateShader(shader_stage_);
  REZERO_DCHECK(shader_name_ > 0);

  const GLchar* source_ptr = static_cast<const GLchar*>(source.c_str());
  glShaderSource(shader_name_, 1, &source_ptr, nullptr);
  glCompileShader(shader_name_);

  GLint status;
  glGetShaderiv(shader_name_, GL_COMPILE_STATUS, &status);
  if (status != GL_TRUE) {
    GLint length = 0;
    glGetShaderiv(shader_name_, GL_INFO_LOG_LENGTH, &length);
    std::unique_ptr<char[]> log_info = std::make_unique<char[]>(length);
    glGetShaderInfoLog(shader_name_, length, nullptr, log_info.get());
    REZERO_LOG(ERROR) << "OpenGL Error: Shader compile error.\n"
                      << "Source code: " << source << "\n"
                      << "Log: " << log_info.get();
    DeleteShader();
    return;
  }

  is_valid_ = true;
}

ShaderGL::~ShaderGL() {
  DeleteShader();
}

void ShaderGL::DeleteShader() {
  is_valid_ = false;
  if (shader_name_ > 0) {
    glDeleteShader(shader_name_);
    shader_name_ = 0;
  }
}

} // namespace gpu
} // namespace rezero
