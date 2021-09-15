// Created by Dong Zhong on 2021/09/14.

#include "rezero/base/task_runner.h"

#include "rezero/base/logging.h"
#include "rezero/base/message_loop_impl.h"

namespace rezero {

TaskRunner::TaskRunner(const std::shared_ptr<MessageLoopImpl>& message_loop)
    : message_loop_(message_loop) {}

TaskRunner::~TaskRunner() = default;

void TaskRunner::PostTask(const Closure& task) {
  message_loop_->PostTask(task, TimePoint::Now());
}

void TaskRunner::PostTaskForTime(const Closure& task, TimePoint time) {
  message_loop_->PostTask(task, time);
}

void TaskRunner::PostDelayedTask(const Closure& task, TimeDelta delay) {
  message_loop_->PostTask(task, TimePoint::Now() + delay);
}

bool TaskRunner::RunTasksOnCurrentThread() {
  // TODO:
  return true;
}

void TaskRunner::RunNowOrPostTask(std::shared_ptr<TaskRunner> task_runner,
                                  const Closure& task) {
  REZERO_CHECK(task_runner);
  if (task_runner->RunTasksOnCurrentThread()) {
    task();
  } else {
    task_runner->PostTask(std::move(task));
  }
}

} // namespace rezero
