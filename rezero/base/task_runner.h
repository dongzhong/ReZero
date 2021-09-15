// Created by Dong Zhong on 2021/09/14.

#ifndef REZERO_BASE_TASK_RUNNER_H_
#define REZERO_BASE_TASK_RUNNER_H_

#include <memory>

#include "rezero/base/closure.h"
#include "rezero/base/macros.h"
#include "rezero/base/time/time_point.h"

namespace rezero {

class MessageLoopImpl;

class TaskRunner {
 public:
  TaskRunner(const std::shared_ptr<MessageLoopImpl>& message_loop);
  virtual ~TaskRunner();

  virtual void PostTask(const Closure& task);

  virtual void PostTaskForTime(const Closure& task, TimePoint time);

  virtual void PostDelayedTask(const Closure& task, TimeDelta delay);

  virtual bool RunTasksOnCurrentThread();

  static void RunNowOrPostTask(std::shared_ptr<TaskRunner> task_runner,
                               const Closure& task);

 private:
  std::shared_ptr<MessageLoopImpl> message_loop_;

  REZERO_DISALLOW_COPY_AND_ASSIGN(TaskRunner);
};

} // namespace rezero

#endif // REZERO_BASE_TASK_RUNNER_H_