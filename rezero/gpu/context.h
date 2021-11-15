// Created by Dong Zhong on 2021/11/12.

#ifndef REZERO_GPU_CONTEXT_H_
#define REZERO_GPU_CONTEXT_H_

#include <memory>

#include "rezero/base/macros.h"
#include "rezero/gpu/enums.h"
#include "rezero/gpu/types.h"

namespace rezero {
namespace gpu {

class SwapChain;

class Context {
 public:
  static std::shared_ptr<Context> CreateNewContext(RenderingApi rendering_api = RenderingApi::kDefault);

  Context();
  virtual ~Context();

  virtual void Initialize() = 0;
  virtual void Terminate() = 0;

  virtual std::shared_ptr<SwapChain> CreateSwapChain(void* native_window) = 0;
  virtual void DestroySwapChain(const std::shared_ptr<SwapChain>& swap_chain) = 0;

  virtual bool MakeCurrent(const std::shared_ptr<SwapChain>& draw,
                           const std::shared_ptr<SwapChain>& read) = 0;

  virtual bool Commit(const std::shared_ptr<SwapChain>& swap_chain) = 0;

  bool IsInitialized() const { return initialized_; }

 protected:
  bool initialized_ = false;

 private:
  REZERO_DISALLOW_COPY_AND_ASSIGN(Context);
};

} // namespace gpu
} // namespace rezero

#endif // REZERO_GPU_CONTEXT_H_
