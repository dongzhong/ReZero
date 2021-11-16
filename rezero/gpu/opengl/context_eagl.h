// Created by Dong Zhong on 2021/11/12.

#ifndef REZERO_GPU_OPENGL_CONTEXT_EAGL_H_
#define REZERO_GPU_OPENGL_CONTEXT_EAGL_H_

#include "rezero/gpu/context.h"

namespace rezero {
namespace gpu {

struct ContextEAGLImpl;

class ContextEAGL final : public Context {
 public:
  ContextEAGL();
  ~ContextEAGL() override;

  void Initialize() override;

  void Terminate() override;

  std::shared_ptr<SwapChain> CreateSwapChain(void* native_window) override;

  void DestroySwapChain(const std::shared_ptr<SwapChain>& swap_chain) override;

  bool MakeCurrent(const std::shared_ptr<SwapChain>& draw,
                   const std::shared_ptr<SwapChain>& read) override;

  bool Commit(const std::shared_ptr<SwapChain>& swap_chain) override;

  std::shared_ptr<Device> CreateNewDevice() override;

 private:
  ContextEAGLImpl* impl_ = nullptr;

  REZERO_DISALLOW_COPY_AND_ASSIGN(ContextEAGL);
};

} // namespace gpu
} // namespace rezero

#endif // REZERO_GPU_OPENGL_CONTEXT_EAGL_H_
