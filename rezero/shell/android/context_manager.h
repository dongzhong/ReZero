// Created by Dong Zhong on 2021/09/26.

#ifndef REZERO_SHELL_ANDROID_CONTEXT_MANAGER_H_
#define REZERO_SHELL_ANDROID_CONTEXT_MANAGER_H_

#include <memory>

#include "rezero/base/macros.h"
#include "rezero/shell/android/native_window_android.h"

namespace rezero {
namespace shell {

enum class RenderingAPI {
  kOpenGLES,
  // TODO: Maybe support Vulkan
};

class ContextManager {
 public:
  ContextManager(RenderingAPI rendering_api);
  virtual ~ContextManager();

  RenderingAPI GetRenderingAPI() const { return rendering_api_; }

  virtual bool Initialize() = 0;
  virtual bool Release() = 0;

  virtual bool CreateOnscreenSurface(const std::shared_ptr<NativeWindowAndroid>& native_window) = 0;
  virtual void TeardownOnscreenSurface() = 0;
  virtual bool IsOnscreenSurfaceValid() = 0;

  virtual bool Present() = 0;

  virtual std::pair<int, int> GetSurfaceSize() = 0;
  virtual bool OnscreenSurfaceSizeChanged(int width, int height) = 0;

 private:
  const RenderingAPI rendering_api_;

  REZERO_DISALLOW_COPY_AND_ASSIGN(ContextManager);
};

} // namespace shell
} // namespace rezero

#endif // REZERO_SHELL_ANDROID_CONTEXT_MANAGER_H_