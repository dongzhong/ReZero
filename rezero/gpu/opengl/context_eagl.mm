// Created by Dong Zhong on 2021/11/12.

#include "rezero/gpu/opengl/context_eagl.h"

#import <OpenGLES/EAGL.h>
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>

#include "rezero/base/logging.h"
#include "rezero/base/ios/scoped_nsobject.h"
#include "rezero/gpu/opengl/device_gl.h"
#include "rezero/gpu/opengl/swap_chain_eagl.h"

namespace rezero {
namespace gpu {

struct ContextEAGLImpl {
  scoped_nsobject<CAEAGLLayer> gl_layer_;
  scoped_nsobject<EAGLContext> context_;
  GLuint default_framebuffer_ = 0;
  GLuint default_renderbuffer_ = 0;
  CGRect current_gl_layer_rect_;
};

ContextEAGL::ContextEAGL()
    : impl_(new ContextEAGLImpl()) {}

ContextEAGL::~ContextEAGL() = default;

void ContextEAGL::Initialize() {
  impl_->context_.reset(
      [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES3]);
  if (!impl_->context_) {
    impl_->context_.reset(
        [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2]);
  }

  if (!impl_->context_) {
    REZERO_LOG(ERROR) << "Failed to create GL context.";
    return;
  }

  [EAGLContext setCurrentContext:impl_->context_];

  // Create default framebuffer and attachment.
  GLuint framebuffer;
  GLuint renderbuffer;
  glGenFramebuffers(1, &framebuffer);
  glGenRenderbuffers(1, &renderbuffer);

  glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
  glBindRenderbuffer(GL_RENDERBUFFER, renderbuffer);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, renderbuffer);

  impl_->default_framebuffer_ = framebuffer;
  impl_->default_renderbuffer_ = renderbuffer;

  initialized_ = true;
}

void ContextEAGL::Terminate() {
  [EAGLContext setCurrentContext:nil];
  impl_->context_.reset();
}

std::shared_ptr<SwapChain> ContextEAGL::CreateSwapChain(void* native_window) {
  if (native_window == nullptr) {
    return nullptr;
  }

  CAEAGLLayer* layer = (__bridge CAEAGLLayer*) native_window;
  return std::make_shared<SwapChainEAGL>(scoped_nsobject<CAEAGLLayer>{[layer retain]});
}

void ContextEAGL::DestroySwapChain(const std::shared_ptr<SwapChain>& swap_chain) {
  if (swap_chain != nullptr && !swap_chain->IsValid()) {
    swap_chain->SetValid(false);
  }
}

bool ContextEAGL::MakeCurrent(const std::shared_ptr<SwapChain>& draw,
                              const std::shared_ptr<SwapChain>& read) {
  REZERO_DCHECK(draw == read);

  if (draw != nullptr && draw->IsValid()) {
    [EAGLContext setCurrentContext:impl_->context_];

    auto eagl_swap_chain = std::dynamic_pointer_cast<SwapChainEAGL>(draw);
    CAEAGLLayer* gl_layer = eagl_swap_chain->GetGLLayer();
    if (gl_layer != impl_->gl_layer_ ||
        !CGRectEqualToRect(impl_->current_gl_layer_rect_, gl_layer.bounds)) {
      impl_->gl_layer_.reset([gl_layer retain]);
      impl_->current_gl_layer_rect_ = gl_layer.bounds;

      glBindFramebuffer(GL_FRAMEBUFFER, impl_->default_framebuffer_);
      glBindRenderbuffer(GL_RENDERBUFFER, impl_->default_renderbuffer_);
      [impl_->context_ renderbufferStorage:GL_RENDERBUFFER
                              fromDrawable:gl_layer];

      GLenum statue = glCheckFramebufferStatus(GL_FRAMEBUFFER);
      REZERO_DCHECK(statue == GL_FRAMEBUFFER_COMPLETE);
    }

    return true;
  }

  return false;
}

bool ContextEAGL::Commit(const std::shared_ptr<SwapChain>& swap_chain) {
  auto eagl_swap_chain = std::dynamic_pointer_cast<SwapChainEAGL>(swap_chain);
  if (eagl_swap_chain != nullptr && eagl_swap_chain->IsValid()) {
    glBindRenderbuffer(GL_RENDERBUFFER, impl_->default_renderbuffer_);

    return [impl_->context_ presentRenderbuffer:GL_RENDERBUFFER];
  }
  return true;
}

std::shared_ptr<Device> ContextEAGL::CreateNewDevice() {
  return std::make_shared<DeviceGL>();
}

} // namespace gpu
} // namespace rezero
