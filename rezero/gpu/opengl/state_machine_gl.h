// Created by Dong Zhong on 2021/10/29.

#ifndef REZERO_GPU_OPENGL_STATE_MACHINE_GL_H_
#define REZERO_GPU_OPENGL_STATE_MACHINE_GL_H_

#include "rezero/base/thread_singleton.h"
#include "rezero/gpu/opengl/includes.h"

namespace rezero {
namespace gpu {

class StateMachineGL : public ThreadSingleton<StateMachineGL> {
 public:
  StateMachineGL();
  ~StateMachineGL();

  void BindBuffer(GLenum buffer_type, GLuint buffer_name);
  void UnbindBuffer(GLenum buffer_type, GLuint buffer_name);

 private:
  GLuint bound_array_buffer_ = 0;
  GLuint bound_element_array_buffer_ = 0;

  REZERO_DISALLOW_COPY_AND_ASSIGN(StateMachineGL);
};

} // namespace gpu
} // namespace rezero

#endif // REZERO_GPU_OPENGL_STATE_MACHINE_GL_H_
