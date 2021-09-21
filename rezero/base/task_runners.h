// Created by Dong Zhong on 2021/09/18.

#ifndef REZERO_BASE_TASK_RUNNERS_H_
#define REZERO_BASE_TASK_RUNNERS_H_

#include "rezero/base/task_runner.h"

namespace rezero {

class TaskRunners {
 public:
  TaskRunners(const std::shared_ptr<TaskRunner>& platform_task_runner,
              const std::shared_ptr<TaskRunner>& main_task_runner);
  ~TaskRunners();

  std::shared_ptr<TaskRunner> GetPlatformTaskRunner() const;

  std::shared_ptr<TaskRunner> GetMainTaskRunner() const;

 private:
  std::shared_ptr<TaskRunner> platform_task_runner_;
  std::shared_ptr<TaskRunner> main_task_runner_;
};

} // namespace rezero

#endif // REZERO_BASE_TASK_RUNNERS_H_