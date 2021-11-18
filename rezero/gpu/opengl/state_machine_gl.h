// Created by Dong Zhong on 2021/11/15.

#ifndef REZERO_GPU_OPENGL_STATE_MACHINE_GL_H_
#define REZERO_GPU_OPENGL_STATE_MACHINE_GL_H_

#include <array>
#include <unordered_map>

#include "rezero/base/thread_singleton.h"
#include "rezero/gpu/opengl/includes_gl.h"

namespace rezero {
namespace gpu {

class StateMachineGL final : public ThreadSingleton<StateMachineGL> {
 public:
  StateMachineGL();
  ~StateMachineGL();

  void BindBuffer(GLenum target, GLuint buffer_name);
  void UnbindBuffer(GLenum target, GLuint buffer_name);

  void UseProgram(GLuint program);
  void UnuseProgram(GLuint program);

  void ActiveTextureUnit(int unit);

  void BindTexture(int unit, GLenum target, GLuint texture);
  void UnbindTexture(GLenum target, GLuint texture);
  void UnbindTextureAtUnit(int unit, GLenum target, GLuint texture);

 private:
  GLuint bound_vertex_buffer_ = 0;
  GLuint bound_index_buffer_ = 0;

  GLuint used_program_ = 0;

  GLint active_texture_unit_ = 0;
  std::array<std::unordered_map<GLenum, GLuint>, kMaxTextureUnits> bound_textures_ = {};

  REZERO_DISALLOW_COPY_AND_ASSIGN(StateMachineGL);
};

} // namespace gpu
} // namespace rezero

#endif // REZERO_GPU_OPENGL_STATE_MACHINE_GL_H_
