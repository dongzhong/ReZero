// Created by Dong Zhong on 2021/10/28.

#ifndef REZERO_GPU_PROGRAM_STATE_H_
#define REZERO_GPU_PROGRAM_STATE_H_

#include "rezero/base/macros.h"

namespace rezero {
namespace gpu {

class ProgramState {
 public:
  ProgramState();
  ~ProgramState();

 private:
  REZERO_DISALLOW_COPY_AND_ASSIGN(ProgramState);
};

} // namespace gpu
} // namespace rezero

#endif // REZERO_GPU_PROGRAM_STATE_H_
