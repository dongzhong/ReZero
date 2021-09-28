// Created by Dong Zhong on 2021/09/26.

#ifndef REZERO_SHELL_ANDROID_CONTEXT_MANAGER_GL_H_
#define REZERO_SHELL_ANDROID_CONTEXT_MANAGER_GL_H_

#include <EGL/egl.h>

#include "rezero/shell/android/context_manager.h"

namespace rezero {
namespace shell {

class ContextManagerGL final : public ContextManager {
 public:
  ContextManagerGL();
  ~ContextManagerGL() override;

  bool Initialize() override;
  bool Release() override;

  bool CreateOnscreenSurface(const std::shared_ptr<NativeWindowAndroid>& native_window) override;
  void TeardownOnscreenSurface() override;
  bool IsOnscreenSurfaceValid() override;

  bool Present() override;

  std::pair<int, int> GetSurfaceSize() override;
  bool OnscreenSurfaceSizeChanged(int width, int height) override;

 private:
  bool InitDisplay();
  void ReleaseDisplay();

  bool ChooseConfiguration();

  bool CreateContext(EGLContext share = EGL_NO_CONTEXT);
  void DestroyContext();

  bool MakeCurrent();
  bool ClearCurrent();

  std::shared_ptr<NativeWindowAndroid> native_window_;
  EGLDisplay display_;
  EGLConfig config_;
  EGLContext context_;
  EGLSurface onscreen_surface_;

  REZERO_DISALLOW_COPY_AND_ASSIGN(ContextManagerGL);
};

} // namespace shell
} // namespace rezero

#endif // REZERO_SHELL_ANDROID_CONTEXT_MANAGER_GL_H_