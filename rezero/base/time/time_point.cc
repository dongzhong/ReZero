// Created by Dong Zhong on 2021/09/13.

#include "rezero/base/time/time_point.h"

#include <chrono>

namespace rezero {

TimePoint TimePoint::Now() {
  const auto elapsed_time = std::chrono::steady_clock::now().time_since_epoch();
  return TimePoint(
      std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed_time).count());
}

} // namespace rezero