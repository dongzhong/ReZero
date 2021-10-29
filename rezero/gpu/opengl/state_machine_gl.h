// Created by Dong Zhong on 2021/10/29.

#ifndef REZERO_GPU_OPENGL_STATE_MACHINE_GL_H_
#define REZERO_GPU_OPENGL_STATE_MACHINE_GL_H_

#include "rezero/base/thread_singleton.h"

namespace rezero {
namespace gpu {

class StateMachineGL : public ThreadSingleton<StateMachineGL> {
 public:
  StateMachineGL();
  ~StateMachineGL();

 private:
  REZERO_DISALLOW_COPY_AND_ASSIGN(StateMachineGL);
};

} // namespace gpu
} // namespace rezero

#endif // REZERO_GPU_OPENGL_STATE_MACHINE_GL_H_
