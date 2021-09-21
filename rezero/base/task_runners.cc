// Created by Dong Zhong on 2021/09/18.

#include "rezero/base/task_runners.h"

#include "rezero/base/logging.h"

namespace rezero {

TaskRunners::TaskRunners(const std::shared_ptr<TaskRunner>& platform_task_runner,
                         const std::shared_ptr<TaskRunner>& main_task_runner)
    : platform_task_runner_(platform_task_runner),
      main_task_runner_(main_task_runner) {
  REZERO_DCHECK(platform_task_runner_);
  REZERO_DCHECK(main_task_runner_);
}

TaskRunners::~TaskRunners() = default;

std::shared_ptr<TaskRunner> TaskRunners::GetPlatformTaskRunner() const {
  return platform_task_runner_;
}

std::shared_ptr<TaskRunner> TaskRunners::GetMainTaskRunner() const {
  return main_task_runner_;
}

} // namespace rezero