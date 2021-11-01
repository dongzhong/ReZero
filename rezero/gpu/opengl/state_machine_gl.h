// Created by Dong Zhong on 2021/10/29.

#ifndef REZERO_GPU_OPENGL_STATE_MACHINE_GL_H_
#define REZERO_GPU_OPENGL_STATE_MACHINE_GL_H_

#include <array>
#include <unordered_map>
#include <utility>

#include "rezero/base/thread_singleton.h"
#include "rezero/gpu/opengl/includes.h"
#include "rezero/gpu/opengl/utils.h"

namespace rezero {
namespace gpu {

class StateMachineGL : public ThreadSingleton<StateMachineGL> {
 public:
  StateMachineGL();
  ~StateMachineGL();

  void BindBuffer(GLenum buffer_type, GLuint buffer_name);
  void UnbindBuffer(GLenum buffer_type, GLuint buffer_name);

  void BindTexture(int unit, GLenum texture_type, GLuint texture_name);
  void UnbindTexture(int unit, GLenum texture_type, GLuint texture_name);
  void UnbindTextureForAllUnit(GLenum texture_type, GLuint texture_name);

  void UseProgram(GLuint program);
  void UnuseProgram(GLuint program);

 private:
  GLuint bound_array_buffer_ = 0;
  GLuint bound_element_array_buffer_ = 0;

  // key: texture slot
  unsigned int active_texture_unit_ = 0;
  std::array<std::unordered_map<GLenum, GLuint>, kMaxTextureUnits> bound_textures_ = {};

  GLuint used_program_ = 0;

  REZERO_DISALLOW_COPY_AND_ASSIGN(StateMachineGL);
};

} // namespace gpu
} // namespace rezero

#endif // REZERO_GPU_OPENGL_STATE_MACHINE_GL_H_
