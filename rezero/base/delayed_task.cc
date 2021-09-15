// Created by Dong Zhong on 2021/09/14.

#include "rezero/base/delayed_task.h"

namespace rezero {

DelayedTask::DelayedTask(size_t order,
                         const Closure& task,
                         TimePoint target_time)
    : order_(order), task_(task), target_time_(target_time) {}

DelayedTask::DelayedTask(const DelayedTask& other) = default;

DelayedTask::~DelayedTask() = default;

const Closure& DelayedTask::GetTask() const {
  return task_;
}

TimePoint DelayedTask::GetTargetTime() const {
  return target_time_;
}

bool DelayedTask::operator>(const DelayedTask& other) const {
  if (target_time_ == other.target_time_) {
    return order_ > other.order_;
  }

  return target_time_ > other.target_time_;
}

} // namespace rezero
