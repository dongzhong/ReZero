// Created by Dong Zhong on 2021/09/17.

#include "rezero/shell/ios/platform_view_ios.h"

#include "rezero/base/logging.h"

namespace rezero {
namespace shell {

PlatformViewIos::PlatformViewIos(
    const std::shared_ptr<TaskRunner>& main_task_runner,
    const scoped_nsobject<CALayer>& layer)
    : PlatformView(main_task_runner),
      layer_(layer) {
  REZERO_DCHECK(layer_);
}

PlatformViewIos::~PlatformViewIos() = default;

} // namespace shell
} // namespace rezero
