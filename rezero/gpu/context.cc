// Created by Dong Zhong on 2021/11/12.

#include "rezero/gpu/context.h"

#include "rezero/base/build_config.h"

#if defined(REZERO_PLATFORM_ANDROID)

#include "rezero/gpu/opengl/context_egl.h"

#elif defined(REZERO_PLATFORM_IOS)

#include "rezero/gpu/opengl/context_eagl.h"

#endif // defined(REZERO_PLATFORM_ANDROID)

namespace rezero {
namespace gpu {

std::shared_ptr<Context> Context::CreateNewContext(RenderingApi rendering_api) {
  if (rendering_api == RenderingApi::kDefault) {
#if defined(REZERO_PLATFORM_ANDROID)
    rendering_api = RenderingApi::kOpenGL;
#elif defined(REZERO_PLATFORM_IOS)
    rendering_api = RenderingApi::kOpenGL;
#endif // defined(REZERO_PLATFORM_ANDROID)
  }

  switch (rendering_api) {
    case RenderingApi::kOpenGL:
#if defined(REZERO_PLATFORM_ANDROID)
      return std::make_shared<ContextEGL>();
#elif defined(REZERO_PLATFORM_IOS)
      return std::make_shared<ContextEAGL>();
#else
      return nullptr;
#endif // defined(REZERO_PLATFORM_ANDROID)
    default:
      return nullptr;
  }
}

Context::Context() = default;

Context::~Context() = default;

} // namespace gpu
} // namespace rezero
