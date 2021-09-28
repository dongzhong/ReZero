// Created by Dong Zhong on 2021/09/17.

#include "rezero/shell/ios/platform_view_ios.h"

#include "rezero/base/logging.h"
#include "rezero/base/waitable_event.h"
#include "rezero/shell/ios/context_manager_gl.h"
#include "rezero/shell/ios/vsync_waiter_ios.h"

namespace rezero {
namespace shell {

PlatformViewIos::PlatformViewIos(
    const std::shared_ptr<TaskRunners>& task_runners,
    const scoped_nsobject<CALayer>& layer)
    : PlatformView(task_runners),
      layer_(layer) {
  REZERO_DCHECK(layer_);

  context_manager_ = ContextManager::Create(layer);

  AutoResetWaitableEvent platform_latch;
  AutoResetWaitableEvent main_latch;
  task_runners_->GetMainTaskRunner()->PostTask([this, &platform_latch, &main_latch]() {
    is_context_initialized_ = context_manager_->Initialize();
    if (is_context_initialized_) {
      is_context_initialized_ = context_manager_->CreateRenderTarget();
    }
    platform_latch.Signal();
    main_latch.Wait();
  });
  platform_latch.Wait();

  is_context_initialized_ = context_manager_->UpdateStorageSizeIfNecessary();

  task_runners_->GetMainTaskRunner()->PostTask([this, &platform_latch]() {
    is_context_initialized_ = context_manager_->MakeCurrent();
    platform_latch.Signal();
  });
  main_latch.Signal();
  platform_latch.Wait();

  vsync_waiter_ = std::make_shared<VsyncWaiterIos>(task_runners_);
}

PlatformViewIos::~PlatformViewIos() {
  context_manager_->Release();
}

bool PlatformViewIos::UpdateStorageSizeIfNecessary() {
  // Running in Platform thread

  AutoResetWaitableEvent platform_latch;
  AutoResetWaitableEvent main_latch;

  task_runners_->GetMainTaskRunner()->PostTask([&platform_latch, &main_latch]() {
    platform_latch.Signal();
    main_latch.Wait();
  });
  platform_latch.Wait();

  bool success = context_manager_->UpdateStorageSizeIfNecessary();
  main_latch.Signal();

  task_runners_->GetMainTaskRunner()->PostTask([this, &success, &platform_latch]() {
    success = context_manager_->MakeCurrent();
    platform_latch.Signal();
  });
  platform_latch.Wait();

  return success;
}

bool PlatformViewIos::Present() {
  // Running in main thread.

  if (!context_manager_->IsRenderTargetValid()) {
    return false;
  }
  return context_manager_->Present();
}

} // namespace shell
} // namespace rezero
