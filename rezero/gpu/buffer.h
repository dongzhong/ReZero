// Created by Dong Zhong on 2021/10/28.

#ifndef REZERO_GPU_BUFFER_H_
#define REZERO_GPU_BUFFER_H_

#include "rezero/gpu/defines.h"
#include REZERO_GPU_BACKEND(buffer.h)

namespace rezero {
namespace gpu {

class Buffer {
 public:
  Buffer();
  ~Buffer();

 private:
  using InternalBuffer = ImplType<Buffer>::type;
  InternalBuffer buffer_;

  REZERO_DISALLOW_COPY_AND_ASSIGN(Buffer);
};

} // namespace gpu
} // namespace rezero

#endif // REZERO_GPU_BUFFER_H_
