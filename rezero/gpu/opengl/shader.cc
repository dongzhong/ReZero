// Created by Dong Zhong on 2021/10/31.

#include "rezero/gpu/shader.h"

#include "rezero/base/logging.h"
#include "rezero/gpu/opengl/utils.h"

namespace rezero {
namespace gpu {

static bool CompileShaderGL(GLuint shader_name, const GLchar* const* source) {
  if (shader_name == 0) {
    return false;
  }

  glShaderSource(shader_name, 1, source, nullptr);
  glCompileShader(shader_name);

  GLint status = 0;
  glGetShaderiv(shader_name, GL_COMPILE_STATUS, &status);
  if (status != GL_TRUE) {
    GLint log_length = 0;
    glGetShaderiv(shader_name, GL_INFO_LOG_LENGTH, &log_length);
    std::unique_ptr<char[]> log_info = std::make_unique<char[]>(log_length);
    glGetShaderInfoLog(shader_name, log_length, nullptr, log_info.get());
    REZERO_LOG(ERROR) << "OpenGL Error: Shader compile error.\n"
                      << "Source code: " << source << "\n"
                      << "Log: " << log_info.get();
    return false;
  }

  return true;
}

static void DeleteShaderGL(GLuint& shader_name) {
  if (shader_name > 0) {
    glDeleteShader(shader_name);
    shader_name = 0;
  }
}

Shader::Shader(ShaderStage stage, const std::string& source)
    : stage_(stage), source_(source) {
  shader_.shader_type_ = Utils::ToGLShaderStage(stage);
  shader_.shader_name_ = glCreateShader(shader_.shader_type_);
  REZERO_DCHECK(shader_.shader_name_ > 0);

  const GLchar* source_ptr = reinterpret_cast<const GLchar*>(source.c_str());
  is_valid_ = CompileShaderGL(shader_.shader_name_, &source_ptr);

  if (!is_valid_) {
    DeleteShaderGL(shader_.shader_name_);
  }
}

Shader::~Shader() {
  is_valid_ = false;
  DeleteShaderGL(shader_.shader_name_);
}

} // namespace gpu
} // namespace rezero
