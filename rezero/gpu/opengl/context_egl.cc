// Created by Dong Zhong on 2021/11/12.

#include "rezero/gpu/opengl/context_egl.h"

#include "rezero/base/logging.h"
#include "rezero/base/size.h"
#include "rezero/gpu/opengl/device_gl.h"

namespace rezero {
namespace gpu {

namespace {

struct EGLNameErrorPair {
  const char* name;
  EGLint code;
};

} // namespace

static EGLNameErrorPair GetLastEGLError() {
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
      return pairs[i];
    }
  }

  const EGLNameErrorPair unknown_error = {
      "Unknown",
      0
  };

  return unknown_error;
}

ContextEGL::ContextEGL() = default;

ContextEGL::~ContextEGL() = default;

namespace {

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

const EGLint context_attributes[] = {
    EGL_CONTEXT_CLIENT_VERSION, 2,
    EGL_NONE,
};

EGLint pbuffer_attribs[] = {
    EGL_WIDTH,  1,
    EGL_HEIGHT, 1,
    EGL_NONE
};

} // namespace

void ContextEGL::Initialize() {
  EGLint config_count = 0;
  EGLConfig config = nullptr;

  // Display
  display_ = eglGetDisplay(EGL_DEFAULT_DISPLAY);
  REZERO_DCHECK(display_ != EGL_NO_DISPLAY);

  if (!eglInitialize(display_, nullptr, nullptr)) {
    auto error = GetLastEGLError();
    REZERO_LOG(ERROR) << "Failed to initialize EGLDisplay. "
                      << "EGL error: [ " << error.name << ", " << error.code << " ].";
    goto failed;
  }

  // Config
  if (eglChooseConfig(display_, config_attributes, &config, 1, &config_count) != EGL_TRUE) {
    config_ = EGL_NO_CONFIG_KHR;
    auto error = GetLastEGLError();
    REZERO_LOG(ERROR) << "Failed to choose config. "
                      << "EGL error: [ " << error.name << ", " << error.code << " ].";
    goto failed;
  }

  if (config_count == 0) {
    REZERO_LOG(ERROR) << "EGL config count is 0.";
    goto failed;
  }

  config_ = config;

  // Dummy Surface
  dummy_surface_ = eglCreatePbufferSurface(display_, config_, pbuffer_attribs);
  if (dummy_surface_ == EGL_NO_SURFACE) {
    auto error = GetLastEGLError();
    REZERO_LOG(ERROR) << "Failed to create dummy surface. "
                      << "EGL error: [ " << error.name << ", " << error.code << " ].";
    goto failed;
  }

  // Context
  context_ = eglCreateContext(display_, config_, nullptr, context_attributes);
  if (context_ == EGL_NO_CONTEXT) {
    auto error = GetLastEGLError();
    REZERO_LOG(ERROR) << "Failed to create EGLContext. "
                      << "EGL error: [ " << error.name << ", " << error.code << " ].";
    goto failed;
  }

  // Current
  if (!MakeCurrent(dummy_surface_, dummy_surface_)) {
    auto error = GetLastEGLError();
    REZERO_LOG(ERROR) << "Failed to make current with dummy surface. "
                      << "EGL error: [ " << error.name << ", " << error.code << " ].";
    goto failed;
  }

  initialized_ = true;

  return;

failed:
  initialized_ = false;

  if (dummy_surface_ != EGL_NO_SURFACE) {
    eglDestroySurface(display_, dummy_surface_);
    dummy_surface_ = EGL_NO_SURFACE;
  }

  if (context_ != EGL_NO_CONTEXT) {
    eglDestroyContext(display_, context_);
    context_ = EGL_NO_CONTEXT;
  }

  eglTerminate(display_);
  display_ = EGL_NO_DISPLAY;
  eglReleaseThread();
}

void ContextEGL::Terminate() {
  initialized_ = false;

  eglMakeCurrent(display_, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
  draw_surface_ = EGL_NO_SURFACE;
  read_surface_ = EGL_NO_SURFACE;

  eglDestroySurface(display_, dummy_surface_);
  dummy_surface_ = EGL_NO_SURFACE;

  eglDestroyContext(display_, context_);
  context_ = EGL_NO_CONTEXT;

  eglTerminate(display_);
  display_ = EGL_NO_DISPLAY;

  eglReleaseThread();
}

std::shared_ptr<SwapChain> ContextEGL::CreateSwapChain(void* native_window) {
  EGLSurface surface = eglCreateWindowSurface(display_,
                                              config_,
                                              static_cast<EGLNativeWindowType>(native_window),
                                              nullptr);
  if (surface == EGL_NO_SURFACE) {
    auto error = GetLastEGLError();
    REZERO_LOG(ERROR) << "Failed to create window surface. "
                      << "EGL error: [ " << error.name << ", " << error.code << " ].";
    return nullptr;
  }

  EGLint width;
  EGLint height;
  if (!eglQuerySurface(display_, surface, EGL_WIDTH, &width) ||
      !eglQuerySurface(display_, surface, EGL_HEIGHT, &height)) {
    auto error = GetLastEGLError();
    REZERO_LOG(ERROR) << "Failed to get size of surface. "
                      << "EGL error: [ " << error.name << ", " << error.code << " ].";
    return nullptr;
  }

  auto swap_chain = std::make_shared<SwapChainEGL>(surface);
  swap_chain->SetSize({ width, height });
  return swap_chain;
}

void ContextEGL::DestroySwapChain(const std::shared_ptr<SwapChain>& swap_chain) {
  if (swap_chain != nullptr && swap_chain->IsValid()) {
    auto egl_swap_chain = std::dynamic_pointer_cast<SwapChainEGL>(swap_chain);
    if (egl_swap_chain->GetSurface() == draw_surface_ ||
        egl_swap_chain->GetSurface() == read_surface_) {
      egl_swap_chain->SetValid(false);
      MakeCurrent(dummy_surface_, dummy_surface_);
      eglDestroySurface(display_, egl_swap_chain->GetSurface());
    }
  }
}

bool ContextEGL::MakeCurrent(const std::shared_ptr<SwapChain>& draw,
                             const std::shared_ptr<SwapChain>& read) {
  auto draw_swap_chain = std::dynamic_pointer_cast<SwapChainEGL>(draw);
  auto read_swap_chain = std::dynamic_pointer_cast<SwapChainEGL>(read);
  if ((draw_swap_chain == nullptr ?
           false : (draw_swap_chain->IsValid() &&draw_swap_chain->GetSurface() != EGL_NO_SURFACE)) &&
      (read_swap_chain == nullptr ?
           false : (read_swap_chain->IsValid() && read_swap_chain->GetSurface() != EGL_NO_SURFACE))) {
    auto success = MakeCurrent(draw_swap_chain->GetSurface(), read_swap_chain->GetSurface());
    if (!success) {
      auto error = GetLastEGLError();
      REZERO_LOG(ERROR) << "Failed to make current. "
                        << "EGL error: [ " << error.name << ", " << error.code << " ].";
    }
    return success;
  }
  return false;
}

bool ContextEGL::Commit(const std::shared_ptr<SwapChain>& swap_chain) {
  auto egl_swap_chain = std::dynamic_pointer_cast<SwapChainEGL>(swap_chain);
  if (egl_swap_chain && egl_swap_chain->IsValid() && egl_swap_chain->GetSurface() != EGL_NO_SURFACE) {
    EGLBoolean success = eglSwapBuffers(display_, egl_swap_chain->GetSurface());
    if (!success) {
      auto error = GetLastEGLError();
      REZERO_LOG(ERROR) << "Failed to swap buffer. "
                        << "EGL error: [ " << error.name << ", " << error.code << " ].";
    }
    return success;
  }
  return false;
}

std::shared_ptr<Device> ContextEGL::CreateNewDevice() {
  return std::make_shared<DeviceGL>();
}

EGLBoolean ContextEGL::MakeCurrent(EGLSurface draw_surface, EGLSurface read_surface) {
  if (draw_surface_ != draw_surface || read_surface_ != read_surface) {
    draw_surface_ = draw_surface;
    read_surface_ = read_surface;
    return eglMakeCurrent(display_, draw_surface_, read_surface_, context_);
  }
  return EGL_TRUE;
}

} // namespace gpu
} // namespace rezero