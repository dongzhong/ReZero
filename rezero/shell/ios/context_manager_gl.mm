// Created by Dong Zhong on 2021/09/26.

#include "rezero/shell/ios/context_manager_gl.h"

#include "rezero/base/logging.h"

namespace rezero {
namespace shell {

ContextManagerGL::ContextManagerGL(const scoped_nsobject<CAEAGLLayer>& layer)
    : ContextManager(RenderingApi::kOpenGLES),
      layer_(layer) {
  // TODO:
  REZERO_DCHECK(layer_);
}

bool ContextManagerGL::Initialize() {
  context_.reset([[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES3]);
  if (!context_) {
    context_.reset([[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2]);
  }

  REZERO_DCHECK(context_);

  return MakeCurrent();
}

bool ContextManagerGL::Release() {
  auto res = [EAGLContext setCurrentContext:nil];
  REZERO_DCHECK(res);

  context_.reset();
}

ContextManagerGL::~ContextManagerGL() = default;

bool ContextManagerGL::CreateRenderTarget() {
  REZERO_DCHECK(layer_);
  REZERO_DCHECK(context_);

  if (@available(iOS 9.0, *)) {
    [layer_ setPresentsWithTransaction:YES];
  }

  //REZERO_DCHECK(context_result);
  REZERO_DCHECK(glGetError() == GL_NO_ERROR);

  // generate framebuffer
  glGenFramebuffers(1, &frame_buffer_);
  REZERO_DCHECK(glGetError() == GL_NO_ERROR);
  REZERO_DCHECK(frame_buffer_ != GL_NONE);

  glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer_);
  REZERO_DCHECK(glGetError() == GL_NO_ERROR);

  // setup color attachment
  glGenRenderbuffers(1, &color_buffer_);
  REZERO_DCHECK(glGetError() == GL_NO_ERROR);

  glBindRenderbuffer(GL_RENDERBUFFER, color_buffer_);
  REZERO_DCHECK(glGetError() == GL_NO_ERROR);

  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, color_buffer_);
  REZERO_DCHECK(glGetError() == GL_NO_ERROR);

  NSString* drawableColorFormat = kEAGLColorFormatRGBA8;
  layer_.get().drawableProperties = @{
    kEAGLDrawablePropertyColorFormat : drawableColorFormat,
    kEAGLDrawablePropertyRetainedBacking : @(NO),
  };

  /*if (![context_ renderbufferStorage:GL_RENDERBUFFER fromDrawable:layer_.get()]) {
    return false;
  }

  glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_WIDTH, &storage_size_width_);
  REZERO_DCHECK(glGetError() == GL_NO_ERROR);

  glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_HEIGHT, &storage_size_height_);
  REZERO_DCHECK(glGetError() == GL_NO_ERROR);*/

  is_render_target_valid_ = true;

  return true;
}

bool ContextManagerGL::TeardownRenderTarget() {
  REZERO_DCHECK(context_);

  if (!is_render_target_valid_) {
    return true;
  }

  is_render_target_valid_ = false;

  REZERO_DCHECK(glGetError() == GL_NO_ERROR);

  glDeleteFramebuffers(1, &frame_buffer_);
  glDeleteRenderbuffers(1, &color_buffer_);
  REZERO_DCHECK(glGetError() == GL_NO_ERROR);

  return true;
}

bool ContextManagerGL::IsRenderTargetValid() const {
  return is_render_target_valid_;
}

bool ContextManagerGL::MakeCurrent() {
  return [EAGLContext setCurrentContext:context_] == YES;
}

bool ContextManagerGL::Present() {
  return [context_ presentRenderbuffer:GL_FRAMEBUFFER];
}

std::pair<int, int> ContextManagerGL::GetDrawableSize() {
  REZERO_DCHECK(IsRenderTargetValid());

  return { storage_size_width_, storage_size_height_ };
}

bool ContextManagerGL::UpdateStorageSizeIfNecessary() {
  // Should run in Platform thread.

  const CGSize size = [layer_.get() bounds].size;
  const CGFloat scale = layer_.get().contentsScale;
  const GLint width = size.width * scale;
  const GLint height = size.height * scale;

  if (width == storage_size_width_ && height == storage_size_height_) {
    return true;
  }

  EAGLContext* origin_context = [EAGLContext currentContext];
  MakeCurrent();

  REZERO_DCHECK(glGetError() == GL_NO_ERROR);

  if (![context_ renderbufferStorage:GL_RENDERBUFFER fromDrawable:layer_.get()]) {
    return false;
  }

  glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_WIDTH, &storage_size_width_);
  REZERO_DCHECK(glGetError() == GL_NO_ERROR);

  glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_HEIGHT, &storage_size_height_);
  REZERO_DCHECK(glGetError() == GL_NO_ERROR);

  REZERO_DCHECK(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);

  [EAGLContext setCurrentContext:origin_context];

  return true;
}

} // namespace shell
} // namespace rezero
