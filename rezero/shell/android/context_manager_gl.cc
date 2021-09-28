// Created by Dong Zhong on 2021/09/26.

#include "rezero/shell/android/context_manager_gl.h"

#include <utility>

#include "rezero/base/logging.h"
#include "rezero/base/size.h"

namespace rezero {
namespace shell {

template <typename T>
using EGLResult = std::pair<bool, T>;

static void LogLastEGLError(const char* message) {
  struct EGLNameErrorPair {
    const char* name;
    EGLint code;
  };

#define EGL_ERROR_DESC(a) \
  { #a, a }

  const EGLNameErrorPair pairs[] = {
      EGL_ERROR_DESC(EGL_SUCCESS),
      EGL_ERROR_DESC(EGL_NOT_INITIALIZED),
      EGL_ERROR_DESC(EGL_BAD_ACCESS),
      EGL_ERROR_DESC(EGL_BAD_ALLOC),
      EGL_ERROR_DESC(EGL_BAD_ATTRIBUTE),
      EGL_ERROR_DESC(EGL_BAD_CONTEXT),
      EGL_ERROR_DESC(EGL_BAD_CONFIG),
      EGL_ERROR_DESC(EGL_BAD_CURRENT_SURFACE),
      EGL_ERROR_DESC(EGL_BAD_DISPLAY),
      EGL_ERROR_DESC(EGL_BAD_SURFACE),
      EGL_ERROR_DESC(EGL_BAD_MATCH),
      EGL_ERROR_DESC(EGL_BAD_PARAMETER),
      EGL_ERROR_DESC(EGL_BAD_NATIVE_PIXMAP),
      EGL_ERROR_DESC(EGL_BAD_NATIVE_WINDOW),
      EGL_ERROR_DESC(EGL_CONTEXT_LOST),
  };

#undef EGL_ERROR_DESC

  constexpr const size_t count = size(pairs);

  EGLint error = eglGetError();

  for (size_t i = 0; i < count; ++i) {
    if (pairs[i].code == error) {
      REZERO_LOG(ERROR) << message
                        << " EGL error: [ " << pairs[i].name << ", " << pairs[i].code << " ].";
      return;
    }
  }

  REZERO_LOG(ERROR) << message << " Unknown EGL error.";
}

ContextManagerGL::ContextManagerGL()
    : ContextManager(RenderingAPI::kOpenGLES),
      display_(EGL_NO_DISPLAY),
      config_(nullptr),
      context_(EGL_NO_CONTEXT),
      onscreen_surface_(EGL_NO_SURFACE) {}

ContextManagerGL::~ContextManagerGL() = default;

bool ContextManagerGL::Initialize() {
  if (!InitDisplay()) {
    LogLastEGLError("Could not create an EGL environment.");
    return false;
  }

  if (!ChooseConfiguration()) {
    LogLastEGLError("Could not choose an EGL configuration.");
    return false;
  }

  if (!CreateContext(EGL_NO_CONTEXT)) {
    LogLastEGLError("Could not create an EGL context.");
    return false;
  }

  return true;
}

bool ContextManagerGL::Release() {
  TeardownOnscreenSurface();

  DestroyContext();

  ReleaseDisplay();

  config_ = nullptr;

  return true;
}

bool ContextManagerGL::CreateOnscreenSurface(
    const std::shared_ptr<NativeWindowAndroid>& native_window) {
  if (context_ == EGL_NO_CONTEXT || !native_window) {
    return false;
  }

  TeardownOnscreenSurface();

  const EGLint attributes[] = {
      EGL_NONE,
  };
  onscreen_surface_ = eglCreateWindowSurface(display_, config_, native_window->GetWindow(), attributes);
  if (onscreen_surface_ == EGL_NO_SURFACE) {
    LogLastEGLError("Could not create an EGL on screen surface.");
    MakeCurrent();
    return false;
  }

  return MakeCurrent();
}

void ContextManagerGL::TeardownOnscreenSurface() {
  ClearCurrent();

  if (onscreen_surface_ != EGL_NO_SURFACE) {
    auto res = eglDestroySurface(display_, onscreen_surface_);
    REZERO_DCHECK(res == EGL_TRUE);
  }

  onscreen_surface_ = EGL_NO_SURFACE;
}

bool ContextManagerGL::IsOnscreenSurfaceValid() {
  return onscreen_surface_ != EGL_NO_SURFACE;
}

bool ContextManagerGL::Present() {
  if (!IsOnscreenSurfaceValid()) {
    return false;
  }

  if (eglSwapBuffers(display_, onscreen_surface_) != EGL_TRUE) {
    LogLastEGLError("Could not present current surface.");
    return false;
  }
  return true;
}

std::pair<int, int> ContextManagerGL::GetSurfaceSize() {
  EGLint width = 0;
  EGLint height = 0;

  if (!eglQuerySurface(display_, onscreen_surface_, EGL_WIDTH, &width) ||
      !eglQuerySurface(display_, onscreen_surface_, EGL_HEIGHT, &height)) {
    LogLastEGLError("Could not query EGL surface size.");
    return { 0, 0 };
  }

  return { width, height };
}

bool ContextManagerGL::OnscreenSurfaceSizeChanged(int width, int height) {
  REZERO_DCHECK(IsOnscreenSurfaceValid());
  REZERO_DCHECK(native_window_);

  auto size = GetSurfaceSize();
  if (width == size.first && height == size.second) {
    return true;
  }

  TeardownOnscreenSurface();
  if (!CreateOnscreenSurface(native_window_)) {
    REZERO_LOG(ERROR) << "Could not create an EGL window surface on resize.";
    return false;
  }

  return MakeCurrent();
}

bool ContextManagerGL::InitDisplay() {
  display_ = eglGetDisplay(EGL_DEFAULT_DISPLAY);

  if (display_ == EGL_NO_DISPLAY) {
    return false;
  }

  if (eglInitialize(display_, nullptr, nullptr) != EGL_TRUE) {
    return false;
  }

  return true;
}

void ContextManagerGL::ReleaseDisplay() {
  if (display_ != EGL_NO_DISPLAY) {
    eglTerminate(display_);
  }

  display_ = EGL_NO_DISPLAY;
}

const EGLint config_attributes[] = {
    EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
    EGL_SURFACE_TYPE,    EGL_WINDOW_BIT,
    EGL_RED_SIZE,        8,
    EGL_GREEN_SIZE,      8,
    EGL_BLUE_SIZE,       8,
    EGL_ALPHA_SIZE,      8,
    EGL_DEPTH_SIZE,      24,
    EGL_STENCIL_SIZE,    0,
    EGL_NONE,
};

bool ContextManagerGL::ChooseConfiguration() {
  EGLint config_count = 0;
  EGLConfig config = nullptr;

  if (eglChooseConfig(display_, config_attributes, &config, 1, &config_count) != EGL_TRUE) {
    config_ = nullptr;
    return false;
  }

  if (config_count <= 0) {
    config_ = nullptr;
    return false;
  }

  config_ = config;
  return true;
}

const EGLint context_attributes[] = {
    EGL_CONTEXT_CLIENT_VERSION, 2,
    EGL_NONE,
};

bool ContextManagerGL::CreateContext(EGLContext share) {
  EGLContext context = eglCreateContext(display_, config_, share, context_attributes);

  context_ = context;

  return context_ != EGL_NO_CONTEXT;
}

void ContextManagerGL::DestroyContext() {
  ClearCurrent();

  if (context_ != EGL_NO_CONTEXT) {
    if (eglDestroyContext(display_, context_) != EGL_TRUE) {
      LogLastEGLError("Could not destroy the EGL context. Possible resource leak.");
    }
    context_ = EGL_NO_CONTEXT;
  }
}

bool ContextManagerGL::MakeCurrent() {
  if (eglMakeCurrent(display_, onscreen_surface_, onscreen_surface_, context_) != EGL_TRUE) {
    LogLastEGLError("Could not make the context current.");
    return false;
  }
  return true;
}

bool ContextManagerGL::ClearCurrent() {
  if (eglGetCurrentContext() != context_) {
    return true;
  }

  if (eglMakeCurrent(display_, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT) != EGL_TRUE) {
    LogLastEGLError("Could not clear the current context.");
    return false;
  }

  return true;
}

} // namespace shell
} // namespace rezero