// Created by Dong Zhong on 2021/09/17.

#ifndef REZERO_SHELL_IOS_RENDERING_API_SELECTION_H_
#define REZERO_SHELL_IOS_RENDERING_API_SELECTION_H_

#import <objc/runtime.h>

namespace rezero {
namespace shell {

enum class RenderingApi {
  kOpenGLES,
  // TODO: kMetal in future
};

RenderingApi GetRenderingApiForProcess();

Class GetCALayerClassForRenderingApi(RenderingApi rendering_api);

} // namespace shell
} // namespace rezero

#endif // REZERO_SHELL_IOS_RENDERING_API_SELECTION_H_
