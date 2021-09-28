// Created by Dong Zhong on 2021/09/26.

#include "rezero/shell/ios/context_manager.h"

#include "rezero/base/logging.h"
#include "rezero/shell/ios/context_manager_gl.h"

namespace rezero {
namespace shell {

std::unique_ptr<ContextManager> ContextManager::Create(
    const scoped_nsobject<CALayer>& layer) {
  switch (GetRenderingApiForProcess()) {
    case RenderingApi::kOpenGLES:
      REZERO_DCHECK([layer.get() isKindOfClass:[CAEAGLLayer class]] == YES);
      return std::make_unique<ContextManagerGL>(
          scoped_nsobject<CAEAGLLayer>(
              reinterpret_cast<CAEAGLLayer*>([layer.get() retain])));
    // TODO: Maybe support Metal in future.
    default:
      return nullptr;
  }
}

ContextManager::ContextManager(RenderingApi rendering_api)
    : rendering_api_(rendering_api) {}

ContextManager::~ContextManager() = default;

} // namespace shell
} // namespace rezero
