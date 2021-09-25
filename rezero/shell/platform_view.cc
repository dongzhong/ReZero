// Created by Dong Zhong on 2021/09/16.

#include "rezero/shell/platform_view.h"

#include "rezero/base/logging.h"
#include "rezero/base/waitable_event.h"

namespace rezero {
namespace shell {

PlatformView::PlatformView(const std::shared_ptr<TaskRunners>& task_runners)
    : task_runners_(task_runners) {
  REZERO_DCHECK(task_runners_);

  // TODO:
  is_context_initialized_ = true;
}

PlatformView::~PlatformView() = default;

void PlatformView::Resume() {
  AutoResetWaitableEvent latch;
  TaskRunner::RunNowOrPostTask(
      task_runners_->GetMainTaskRunner(),
      [this, &latch]() {
        if (is_context_initialized_ && !is_running_) {
          is_running_ = true;
          AsyncAwaitVsync();
          // TODO: other options.
        }
        latch.Signal();
      });
  latch.Wait();
}

void PlatformView::Pause() {
  AutoResetWaitableEvent latch;
  TaskRunner::RunNowOrPostTask(
      task_runners_->GetMainTaskRunner(),
      [this, &latch]() {
        if (is_context_initialized_ && is_running_) {
          is_running_ = false;
          // TODO: other options.
        }
        latch.Signal();
      });
  latch.Wait();
}

void PlatformView::AsyncAwaitVsync() {
  if (vsync_waiter_) {
    vsync_waiter_->AsyncWaitForVsync(
        [this](TimePoint start_time, TimePoint end_time) {
          OnVsync(start_time, end_time);
        });
  }
}

void PlatformView::OnVsync(TimePoint start_time, TimePoint end_time) {
  if (is_running_) {
    // TODO: other options.
    AsyncAwaitVsync();
  }
}

} // namespace shell
} // namespace rezero
