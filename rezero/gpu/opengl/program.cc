// Created by Dong Zhong on 2021/10/28.

#include "rezero/gpu/program.h"

#include "rezero/base/logging.h"
#include "rezero/gpu/opengl/state_machine_gl.h"

namespace rezero {
namespace gpu {

static bool CompileProgram(GLuint program_name, GLuint vertex_shader, GLuint fragment_shader) {
  if (program_name == 0 || vertex_shader == 0 || fragment_shader == 0) {
    return false;
  }

  glAttachShader(program_name, vertex_shader);
  glAttachShader(program_name, fragment_shader);

  glLinkProgram(program_name);

  GLint status = 0;
  glGetProgramiv(program_name, GL_LINK_STATUS, &status);
  if (status != GL_TRUE) {
    REZERO_LOG(ERROR) << "OpenGL Error: " << "failed to link program.";
    return false;
  }

  return true;
}

static void ComputeUniformInfo(GLuint program_name,
                               std::unordered_map<std::string, UniformInfo>& uniforms,
                               std::size_t& uniform_buffer_size) {
  if (program_name == 0) {
    return;
  }

  GLint uniform_count = 0;
  glGetProgramiv(program_name, GL_ACTIVE_UNIFORMS, &uniform_count);
  if (uniform_count <= 0) {
    return;
  }

#define MAX_UNIFORM_NAME_LENGTH 256
  UniformInfo uniform;
  GLint length = 0;
  std::unique_ptr<GLchar[]> uniform_name = std::make_unique<GLchar[]>(MAX_UNIFORM_NAME_LENGTH);
  std::size_t offset = 0;
  for (int i = 0; i < uniform_count; ++i) {
    glGetActiveUniform(program_name,
                       static_cast<GLuint>(i),
                       MAX_UNIFORM_NAME_LENGTH,
                       &length,
                       &uniform.count,
                       &uniform.type,
                       uniform_name.get());
    uniform_name.get()[length] = '\0';

    if (length > 3) {
      char* c = strrchr(uniform_name.get(), '[');
      if (c) {
        *c = '\0';
        uniform.is_array = true;
      }
    }
    uniform.location[0] = glGetUniformLocation(program_name, uniform_name.get());
    uniform.size = Utils::GetGLDataTypeSize(uniform.type);
    uniform.location[1] = static_cast<int>(offset);
    offset += uniform.size * uniform.count;
    uniforms[std::string(uniform_name.get())] = uniform;
  }
#undef MAX_UNIFORM_NAME_LENGTH
}

static void ComputeAttributeInfo(GLuint program_name, std::unordered_map<std::string, AttributeInfo>& attributes) {
  if (program_name == 0) {
    return;
  }

  GLint attribute_count = 0;
  glGetProgramiv(program_name, GL_ACTIVE_ATTRIBUTES, &attribute_count);

  if (attribute_count <= 0) {
    return;
  }

#define MAX_ATTRIBUTE_NAME_LENGTH 256
  AttributeInfo attribute_info;
  GLsizei length = 0;
  std::unique_ptr<GLchar[]> name = std::make_unique<GLchar[]>(MAX_ATTRIBUTE_NAME_LENGTH);
  for (int i = 0; i < attribute_count; ++i) {
    glGetActiveAttrib(program_name,
                      static_cast<GLuint>(i),
                      MAX_ATTRIBUTE_NAME_LENGTH,
                      &length,
                      &attribute_info.count,
                      &attribute_info.type,
                      name.get());
    attribute_info.location = glGetAttribLocation(program_name, name.get());
    attribute_info.size = Utils::GetGLDataTypeSize(attribute_info.type);
    attributes[std::string(name.get(), name.get() + length)] = attribute_info;
  }
#undef MAX_ATTRIBUTE_NAME_LENGTH
}

static void DeleteProgram(GLuint& program_name) {
  if (program_name > 0) {
    auto& state_machine = StateMachineGL::GetCurrent();
    state_machine.UnuseProgram(program_name);
    glDeleteProgram(program_name);
    program_name = 0;
  }
}

Program::Program(const std::shared_ptr<Shader>& vertex_shader,
                 const std::shared_ptr<Shader>& fragment_shader)
    : vertex_shader_(vertex_shader),
      fragment_shader_(fragment_shader) {
  REZERO_DCHECK(vertex_shader_ && vertex_shader_->IsValid());
  REZERO_DCHECK(fragment_shader_);

  program_.program_name_ = glCreateProgram();
  REZERO_DCHECK(program_.program_name_ > 0);

  is_valid_ = CompileProgram(program_.program_name_,
                             vertex_shader_->shader_.shader_name_,
                             fragment_shader_->shader_.shader_name_);
  if (!is_valid_) {
    DeleteProgram(program_.program_name_);
    return;
  }

  ComputeUniformInfo(program_.program_name_, program_.uniforms_, program_.uniform_buffer_size_);
  ComputeAttributeInfo(program_.program_name_, program_.attributes_);
}

Program::~Program() {
  is_valid_ = false;
  DeleteProgram(program_.program_name_);
}

UniformInfo Program::GetUniformInfo(const std::string& name) {
  if (auto iter = program_.uniforms_.find(name);
      iter != program_.uniforms_.end()) {
    return iter->second;
  }
  return {};
}

AttributeInfo Program::GetAttributeInfo(const std::string& name) {
  if (auto iter = program_.attributes_.find(name);
      iter != program_.attributes_.end()) {
    return iter->second;
  }
  return {};
}

} // namespace gpu
} // namespace rezero
