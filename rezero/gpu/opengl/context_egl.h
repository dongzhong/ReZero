// Created by Dong Zhong on 2021/11/12.

#ifndef REZERO_GPU_OPENGL_CONTEXT_EGL_H_
#define REZERO_GPU_OPENGL_CONTEXT_EGL_H_

#include <EGL/egl.h>
#include <EGL/eglext.h>

#include "rezero/gpu/context.h"
#include "rezero/gpu/opengl/swap_chain_egl.h"

namespace rezero {
namespace gpu {

class ContextEGL final : public Context {
 public:
  ContextEGL();
  ~ContextEGL() override;

  void Initialize() override;

  void Terminate() override;

  std::shared_ptr<SwapChain> CreateSwapChain(void* native_window) override;

  void DestroySwapChain(const std::shared_ptr<SwapChain>& swap_chain) override;

  bool MakeCurrent(const std::shared_ptr<SwapChain>& draw,
                   const std::shared_ptr<SwapChain>& read) override;

  bool Commit(const std::shared_ptr<SwapChain>& swap_chain) override;

  std::shared_ptr<Device> CreateNewDevice() override;

 private:
  EGLBoolean MakeCurrent(EGLSurface draw_surface, EGLSurface read_surface);

  EGLDisplay display_ = EGL_NO_DISPLAY;
  EGLConfig config_ = EGL_NO_CONFIG_KHR;
  EGLContext context_ = EGL_NO_CONTEXT;
  EGLSurface dummy_surface_ = EGL_NO_SURFACE;

  EGLSurface draw_surface_ = EGL_NO_SURFACE;
  EGLSurface read_surface_ = EGL_NO_SURFACE;

  REZERO_DISALLOW_COPY_AND_ASSIGN(ContextEGL);
};

} // namespace gpu
} // namespace rezero

#endif // REZERO_GPU_OPENGL_CONTEXT_EGL_H_