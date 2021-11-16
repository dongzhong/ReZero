// Created by Dong Zhong on 2021/11/16.

#ifndef REZERO_GPU_OPENGL_PROGRAM_GL_H_
#define REZERO_GPU_OPENGL_PROGRAM_GL_H_

#include <unordered_map>

#include "rezero/gpu/program.h"
#include "rezero/gpu/opengl/includes_gl.h"

namespace rezero {
namespace gpu {

struct AttributeInfo {
  GLuint location_ = 0;
  GLenum type_ = GL_FLOAT;
  std::size_t size_ = 0;
};

struct UniformInfo {
  GLuint location_ = 0;
  GLenum type_ = GL_FLOAT;
  bool is_array_ = false;
  std::size_t size_ = 0;
  std::size_t count_ = 0;
};

class ProgramGL final : public Program {
 public:
  ProgramGL(const std::shared_ptr<Shader>& vertex_shader, const std::shared_ptr<Shader>& fragment_shader);
  virtual ~ProgramGL();

  GLuint GetProgramName() const { return program_name_; }

 private:
  void CalculateAttributes();
  void CalculateUniforms();

  void DeleteProgram();

  GLuint program_name_;

  std::unordered_map<std::string, AttributeInfo> attributes_;

  std::unordered_map<std::string, UniformInfo> uniforms_;

  REZERO_DISALLOW_COPY_AND_ASSIGN(ProgramGL);
};

} // namespace gpu
} // namespace rezero

#endif // REZERO_GPU_OPENGL_PROGRAM_GL_H_
