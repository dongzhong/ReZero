// Created by Dong Zhong on 2021/09/16.

#ifndef REZERO_SHELL_PLATFORM_VIEW_H_
#define REZERO_SHELL_PLATFORM_VIEW_H_

#include "rezero/base/macros.h"
#include "rezero/base/task_runners.h"
#include "rezero/gpu/context.h"
#include "rezero/gpu/swap_chain.h"
#include "rezero/shell/vsync_waiter.h"

namespace rezero {
namespace shell {

using namespace gpu;

class PlatformView {
 public:
  PlatformView(const std::shared_ptr<TaskRunners>& task_runners);
  virtual ~PlatformView();

  void Resume();
  void Pause();

 protected:
  virtual void MakeSwapChainValid() = 0;
  void ReleaseSwapChain();

  std::shared_ptr<TaskRunners> task_runners_;
  std::shared_ptr<VsyncWaiter> vsync_waiter_;

  std::shared_ptr<Context> context_ = nullptr;
  std::shared_ptr<SwapChain> swap_chain_ = nullptr;

 private:
  void AsyncAwaitVsync();
  void OnVsync(TimePoint start_time, TimePoint end_time);

  void UpdateAndDraw(TimePoint start_time, TimePoint end_time);
  bool Present();

  bool is_running_ = false;

  REZERO_DISALLOW_COPY_AND_ASSIGN(PlatformView);
};

} // namespace shell
} // namespace rezero

#endif // REZERO_SHELL_PLATFORM_VIEW_H_
