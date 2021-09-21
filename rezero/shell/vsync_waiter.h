// Created by Dong Zhong on 2021/09/18.

#ifndef REZERO_SHELL_VSYNC_WAITER_H_
#define REZERO_SHELL_VSYNC_WAITER_H_

#include <functional>
#include <mutex>

#include "rezero/base/task_runners.h"
#include "rezero/base/time/time_point.h"

namespace rezero {
namespace shell {

class VsyncWaiter {
 public:
  using Callback = std::function<void(TimePoint, TimePoint)>;

  virtual ~VsyncWaiter();

  void AsyncWaitForVsync(const Callback& callback);

 protected:
  VsyncWaiter(const std::shared_ptr<TaskRunners>& task_runners);

  virtual void AwaitVsync() = 0;

  void FireCallback(TimePoint frame_start_time, TimePoint frame_end_time);

  std::shared_ptr<TaskRunners> task_runners_;

 private:
  std::mutex callback_mutex_;
  Callback callback_;

  REZERO_DISALLOW_COPY_AND_ASSIGN(VsyncWaiter);
};

} // namespace shell
} // namespace rezero

#endif // REZERO_SHELL_VSYNC_WAITER_H_