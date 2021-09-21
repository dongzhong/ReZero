// Created by Dong Zhong on 2021/09/18.

#include "rezero/shell/vsync_waiter.h"

#include "rezero/base/logging.h"

namespace rezero {
namespace shell {

VsyncWaiter::VsyncWaiter(const std::shared_ptr<TaskRunners>& task_runners)
    : task_runners_(task_runners) {
  REZERO_DCHECK(task_runners_);
}

VsyncWaiter::~VsyncWaiter() = default;

void VsyncWaiter::AsyncWaitForVsync(const Callback& callback) {
  if (!callback) {
    return;
  }

  {
    std::scoped_lock lock(callback_mutex_);
    if (callback_) {
      return;
    }

    callback_ = std::move(callback);
  }

  AwaitVsync();
}

void VsyncWaiter::FireCallback(TimePoint frame_start_time, TimePoint frame_end_time) {
  Callback callback;

  {
    std::scoped_lock lock(callback_mutex_);
    callback.swap(callback_);
  }

  if (callback) {
    task_runners_->GetMainTaskRunner()->PostTaskForTime(
        [callback, frame_start_time, frame_end_time]() {
          callback(frame_start_time, frame_end_time);
        },
        frame_start_time);
  }
}

} // namespace shell
} // namespace rezero
