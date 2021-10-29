// Created by Dong Zhong on 2021/10/28.

#ifndef REZERO_GPU_COMMAND_BUFFER_H_
#define REZERO_GPU_COMMAND_BUFFER_H_

#include "rezero/gpu/defines.h"
#include "rezero/gpu/render_pass_descriptor.h"
#include REZERO_GPU_BACKEND(command_buffer.h)

namespace rezero {
namespace gpu {

class CommandBuffer {
 public:
  CommandBuffer();
  ~CommandBuffer();

 private:
  using InternalCommandBuffer = ImplType<CommandBuffer>::type;
  InternalCommandBuffer command_buffer_;

  REZERO_DISALLOW_COPY_AND_ASSIGN(CommandBuffer);
};

} // namespace gpu
} // namespace rezero

#endif // REZERO_GPU_COMMAND_BUFFER_H_
