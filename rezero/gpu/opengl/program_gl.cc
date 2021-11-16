// Created by Dong Zhong on 2021/11/16.

#include "rezero/gpu/opengl/program_gl.h"

#include "rezero/base/logging.h"
#include "rezero/gpu/opengl/shader_gl.h"
#include "rezero/gpu/opengl/state_machine_gl.h"
#include "rezero/gpu/opengl/utils_gl.h"

namespace rezero {
namespace gpu {

ProgramGL::ProgramGL(const std::shared_ptr<Shader>& vertex_shader,
                     const std::shared_ptr<Shader>& fragment_shader)
    : Program(vertex_shader, fragment_shader) {
  program_name_ = glCreateProgram();
  REZERO_DCHECK(program_name_ > 0);

  auto vertex_shader_gl = std::dynamic_pointer_cast<ShaderGL>(vertex_shader_);
  auto fragment_shader_gl = std::dynamic_pointer_cast<ShaderGL>(fragment_shader_);
  REZERO_DCHECK(vertex_shader_gl != nullptr && fragment_shader_gl != nullptr);

  glAttachShader(program_name_, vertex_shader_gl->GetShaderName());
  glAttachShader(program_name_, fragment_shader_gl->GetShaderName());
  glLinkProgram(program_name_);

  GLint status;
  glGetProgramiv(program_name_, GL_LINK_STATUS, &status);
  if (status != GL_TRUE) {
    REZERO_LOG(ERROR) << "Failed to link program.";
    DeleteProgram();
    return;
  }

  is_valid_ = true;

  CalculateAttributes();
  CalculateUniforms();
}

ProgramGL::~ProgramGL() {
  DeleteProgram();
}

void ProgramGL::CalculateAttributes() {
  GLint attribute_count;
  glGetProgramiv(program_name_, GL_ACTIVE_ATTRIBUTES, &attribute_count);

  if (attribute_count <= 0) {
    return;
  }

#define MAX_ATTRIBUTE_NAME_LENGTH 256
  std::unique_ptr<char[]> attribute_name = std::make_unique<char[]>(MAX_ATTRIBUTE_NAME_LENGTH);
  GLsizei length;
  GLint size;
  AttributeInfo attribute_info;
  for (int i = 0; i < attribute_count; ++i) {
    glGetActiveAttrib(program_name_,
                      static_cast<GLuint>(i),
                      MAX_ATTRIBUTE_NAME_LENGTH,
                      &length,
                      &size,
                      &attribute_info.type_,
                      attribute_name.get());
    std::string name(attribute_name.get(), attribute_name.get() + length);
    attribute_info.location_ = glGetAttribLocation(program_name_,
                                                   static_cast<const GLchar*>(name.c_str()));
    attribute_info.size_ = UtilsGL::GetGLDataTypeSize(attribute_info.type_) * size;

    attributes_[name] = attribute_info;
  }

#undef MAX_ATTRIBUTE_NAME_LENGTH
}

void ProgramGL::CalculateUniforms() {
  GLint uniform_count;
  glGetProgramiv(program_name_, GL_ACTIVE_UNIFORMS, &uniform_count);

  if (uniform_count <= 0) {
    return;
  }

#define MAX_UNIFORM_NAME_LENGTH 256
  std::unique_ptr<char[]> uniform_name = std::make_unique<char[]>(MAX_UNIFORM_NAME_LENGTH);
  UniformInfo uniform_info;
  GLsizei length;
  GLint count;
  for (int i = 0; i < uniform_count; ++i) {
    glGetActiveUniform(program_name_,
                       static_cast<GLuint>(i),
                       MAX_UNIFORM_NAME_LENGTH,
                       &length,
                       &count,
                       &uniform_info.type_,
                       uniform_name.get());
    uniform_info.is_array_ = false;
    if (length > 3) {
      char* c = strrchr(uniform_name.get(), '[');
      if (c) {
        *c = '\0';
        uniform_info.is_array_ = true;
      }
    }
    std::string name(uniform_name.get());
    uniform_info.location_ = glGetUniformLocation(program_name_, name.c_str());
    uniform_info.count_ = count;
    uniform_info.size_ = UtilsGL::GetGLDataTypeSize(uniform_info.type_);
    uniforms_[name] = uniform_info;
  }
#undef MAX_UNIFORM_NAME_LENGTH
}

void ProgramGL::DeleteProgram() {
  is_valid_ = false;
  if (program_name_ > 0) {
    if (vertex_shader_ != nullptr && vertex_shader_->IsValid()) {
      auto vertex_shader_gl = std::dynamic_pointer_cast<ShaderGL>(vertex_shader_);
      if (vertex_shader_gl) {
        glDetachShader(program_name_, vertex_shader_gl->GetShaderName());
      }
    }
    if (fragment_shader_ != nullptr && fragment_shader_->IsValid()) {
      auto fragment_shader_gl = std::dynamic_pointer_cast<ShaderGL>(fragment_shader_);
      if (fragment_shader_gl) {
        glDetachShader(program_name_, fragment_shader_gl->GetShaderName());
      }
    }

    auto& state_machine = StateMachineGL::GetCurrent();
    state_machine.UnuseProgram(program_name_);
    glDeleteProgram(program_name_);
    program_name_ = 0;
  }
}

} // namespace gpu
} // namespace rezero
