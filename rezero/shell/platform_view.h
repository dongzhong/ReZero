// Created by Dong Zhong on 2021/09/16.

#ifndef REZERO_SHELL_PLATFORM_VIEW_H_
#define REZERO_SHELL_PLATFORM_VIEW_H_

#include "rezero/base/macros.h"
#include "rezero/base/task_runners.h"
#include "rezero/shell/vsync_waiter.h"

namespace rezero {
namespace shell {

class PlatformView {
 public:
  PlatformView(const std::shared_ptr<TaskRunners>& task_runners);
  virtual ~PlatformView();

  void Resume();
  void Pause();

 protected:
  std::shared_ptr<TaskRunners> task_runners_;
  std::shared_ptr<VsyncWaiter> vsync_waiter_;

  bool is_context_initialized_ = false;

 private:
  void AsyncAwaitVsync();
  void OnVsync(TimePoint start_time, TimePoint end_time);

  bool is_running_ = false;

  REZERO_DISALLOW_COPY_AND_ASSIGN(PlatformView);
};

} // namespace shell
} // namespace rezero

#endif // REZERO_SHELL_PLATFORM_VIEW_H_