// Created by Dong Zhong on 2021/09/26.

#ifndef REZERO_SHELL_IOS_CONTEXT_MANAGER_GL_H_
#define REZERO_SHELL_IOS_CONTEXT_MANAGER_GL_H_

#include "rezero/shell/ios/context_manager.h"

#import <OpenGLES/EAGL.h>
#import <OpenGLES/ES2/gl.h>
#import <QuartzCore/CAEAGLLayer.h>

namespace rezero {
namespace shell {

class ContextManagerGL final : public ContextManager {
 public:
  ContextManagerGL(const scoped_nsobject<CAEAGLLayer>& layer);
  ~ContextManagerGL() override;

  bool Initialize() override;
  bool Release() override;

  bool CreateRenderTarget() override;
  bool TeardownRenderTarget() override;
  bool IsRenderTargetValid() const override;

  bool MakeCurrent() override;

  bool Present() override;

  std::pair<int, int> GetDrawableSize() override;
  bool UpdateStorageSizeIfNecessary() override;

 private:
  scoped_nsobject<CAEAGLLayer> layer_;
  scoped_nsobject<EAGLContext> context_;

  GLuint frame_buffer_ = GL_NONE;
  GLuint color_buffer_ = GL_NONE;
  GLint storage_size_width_ = GL_NONE;
  GLint storage_size_height_ = GL_NONE;
  bool is_render_target_valid_ = false;

  REZERO_DISALLOW_COPY_AND_ASSIGN(ContextManagerGL);
};

} // namespace shell
} // namespace rezero

#endif // REZERO_SHELL_IOS_CONTEXT_MANAGER_GL_H_
