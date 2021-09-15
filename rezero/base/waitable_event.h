// Created by Dong Zhong on 2021/09/14.

#ifndef REZERO_BASE_WAITABLE_EVENT_H_
#define REZERO_BASE_WAITABLE_EVENT_H_

#include <condition_variable>
#include <mutex>

#include "rezero/base/macros.h"
#include "rezero/base/time/time_delta.h"

namespace rezero {

class AutoResetWaitableEvent final {
 public:
  AutoResetWaitableEvent() = default;
  ~AutoResetWaitableEvent() = default;

  void Signal();

  void Reset();

  void Wait();

  bool WaitWithTimeout(TimeDelta timeout);

 private:
  std::condition_variable cv_;
  std::mutex mutex_;

  bool is_signaled_ = false;

  REZERO_DISALLOW_COPY_AND_ASSIGN(AutoResetWaitableEvent);
};

class ManualResetWaitableEvent final {
 public:
  ManualResetWaitableEvent() = default;
  ~ManualResetWaitableEvent() = default;

  void Signal();

  void Reset();

  void Wait();

  bool WaitWithTimeout(TimeDelta timeout);

 private:
  std::condition_variable cv_;
  std::mutex mutex_;

  bool is_signaled_ = false;

  unsigned signal_id_ = 0u;

  REZERO_DISALLOW_COPY_AND_ASSIGN(ManualResetWaitableEvent);
};

} // namespace rezero

#endif // REZERO_BASE_WAITABLE_EVENT_H_