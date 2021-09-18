// Created by Dong Zhong on 2021/09/17.

#include "rezero/shell/ios/rendering_api_selection.h"

#include "rezero/base/logging.h"

#import <QuartzCore/CAEAGLLayer.h>

namespace rezero {
namespace shell {

RenderingApi GetRenderingApiForProcess() {
  return RenderingApi::kOpenGLES;
}

Class GetCALayerClassForRenderingApi(RenderingApi rendering_api) {
  switch (rendering_api) {
    case RenderingApi::kOpenGLES:
      return [CAEAGLLayer class];
  default:
    REZERO_CHECK(false) << "Unknown RenderingApi";
    break;
 }
}

} // namespace shell
} // namespace rezero
