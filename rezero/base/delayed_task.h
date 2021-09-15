// Created by Dong Zhong on 2021/09/14.

#ifndef REZERO_BASE_DELAYED_TASK_H_
#define REZERO_BASE_DELAYED_TASK_H_

#include <queue>

#include "rezero/base/closure.h"
#include "rezero/base/time/time_point.h"

namespace rezero {

class DelayedTask {
 public:
  DelayedTask(size_t order,
              const Closure& task,
              TimePoint target_time);

  DelayedTask(const DelayedTask& other);

  ~DelayedTask();

  const Closure& GetTask() const;

  TimePoint GetTargetTime() const;

  bool operator>(const DelayedTask& other) const;

 private:
  size_t order_;
  Closure task_;
  TimePoint target_time_;
};

using DelayedTaskQueue = std::priority_queue<DelayedTask,
                                             std::deque<DelayedTask>,
                                             std::greater<DelayedTask>>;

} // namespace rezero

#endif // REZERO_BASE_DELAYED_TASK_H_
