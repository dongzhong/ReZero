// Created by Dong Zhong on 2021/09/17.

#include "rezero/shell/ios/platform_view_ios.h"

#include "rezero/base/logging.h"
#include "rezero/base/waitable_event.h"
#include "rezero/shell/ios/vsync_waiter_ios.h"

namespace rezero {
namespace shell {

PlatformViewIos::PlatformViewIos(
    const std::shared_ptr<TaskRunners>& task_runners,
    const scoped_nsobject<CALayer>& layer)
    : PlatformView(task_runners),
      layer_(layer) {
  REZERO_DCHECK(layer_);

  vsync_waiter_ = std::make_shared<VsyncWaiterIos>(task_runners_);
}

PlatformViewIos::~PlatformViewIos() = default;

bool PlatformViewIos::UpdateStorageSizeIfNecessary() {
  // Running in Platform thread
  return true;
}

bool PlatformViewIos::Present() {
  // Running in main thread.
  return true;
}

} // namespace shell
} // namespace rezero
