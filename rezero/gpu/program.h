// Created by Dong Zhong on 2021/10/28.

#ifndef REZERO_GPU_PROGRAM_H_
#define REZERO_GPU_PROGRAM_H_

#include "rezero/gpu/defines.h"
#include REZERO_GPU_BACKEND(program.h)

namespace rezero {
namespace gpu {

class Program {
 public:
  Program();
  ~Program();

 private:
  using InternalProgram = ImplType<Program>::type;
  InternalProgram program_;

  REZERO_DISALLOW_COPY_AND_ASSIGN(Program);
};

} // namespace gpu
} // namespace rezero

#endif // REZERO_GPU_PROGRAM_H_
