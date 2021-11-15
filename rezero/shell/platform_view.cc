// Created by Dong Zhong on 2021/09/16.

#include "rezero/shell/platform_view.h"

#include "rezero/base/logging.h"
#include "rezero/base/waitable_event.h"

namespace rezero {
namespace shell {

PlatformView::PlatformView(const std::shared_ptr<TaskRunners>& task_runners)
    : task_runners_(task_runners) {
  REZERO_DCHECK(task_runners_);

  AutoResetWaitableEvent latch;
  task_runners_->GetMainTaskRunner()->PostTask([this, &latch]() {
    context_ = Context::CreateNewContext(RenderingApi::kDefault);
    REZERO_DCHECK(context_);
    context_->Initialize();
    REZERO_DCHECK(context_->IsInitialized());
    latch.Signal();
  });
  latch.Wait();
}

PlatformView::~PlatformView() {
  AutoResetWaitableEvent latch;
  task_runners_->GetMainTaskRunner()->PostTask([this, &latch]() {
    ReleaseSwapChain();
    context_->Terminate();
    context_.reset();
    latch.Signal();
  });
  latch.Wait();
}

void PlatformView::Resume() {
  AutoResetWaitableEvent latch;
  TaskRunner::RunNowOrPostTask(
      task_runners_->GetMainTaskRunner(),
      [this, &latch]() {
        if (!is_running_) {
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
        if (is_running_) {
          is_running_ = false;

          ReleaseSwapChain();
        }
        latch.Signal();
      });
  latch.Wait();
}

void PlatformView::ReleaseSwapChain() {
  context_->DestroySwapChain(swap_chain_);
  swap_chain_.reset();
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
    UpdateAndDraw(start_time, end_time);
    AsyncAwaitVsync();
  }
}

void PlatformView::UpdateAndDraw(TimePoint start_time, TimePoint end_time) {
  // TODO: Update.
  if (swap_chain_ == nullptr || !swap_chain_->IsValid()) {
    MakeSwapChainValid();
  }

  if (!Present()) {
    REZERO_LOG(ERROR) << "Could not present the current result.";
  }
}

bool PlatformView::Present() {
  if (context_ != nullptr && context_->IsInitialized()) {
    return context_->Commit(swap_chain_);
  }
  return false;
}

} // namespace shell
} // namespace rezero
