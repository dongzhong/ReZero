// Created by Dong Zhong on 2021/09/14.

#include "rezero/base/waitable_event.h"

#include "rezero/base/logging.h"
#include "rezero/base/time/time_point.h"

namespace rezero {

void AutoResetWaitableEvent::Signal() {
  std::scoped_lock lock(mutex_);
  is_signaled_ = true;
  cv_.notify_one();
}

void AutoResetWaitableEvent::Reset() {
  std::scoped_lock lock(mutex_);
  is_signaled_ = false;
}

void AutoResetWaitableEvent::Wait() {
  std::unique_lock lock(mutex_);
  while (!is_signaled_) {
    cv_.wait(lock);
  }
  is_signaled_ = false;
}

bool AutoResetWaitableEvent::WaitWithTimeout(TimeDelta timeout) {
  std::unique_lock lock(mutex_);

  if (is_signaled_) {
    is_signaled_ = false;
    return false;
  }

  TimeDelta wait_remaining = timeout;
  TimePoint start_time = TimePoint::Now();

  while (true) {
    if (std::cv_status::timeout ==
        cv_.wait_for(lock, std::chrono::nanoseconds(wait_remaining.ToNanoseconds()))) {
      return true;
    }

    if (is_signaled_) {
      break;
    }

    TimePoint now = TimePoint::Now();
    REZERO_DCHECK(now >= start_time);
    TimeDelta elapsed = now - start_time;
    if (elapsed >= timeout) {
      return true;
    }

    wait_remaining = timeout - elapsed;
  }

  is_signaled_ = false;
  return false;
}

void ManualResetWaitableEvent::Signal() {
  std::scoped_lock lock(mutex_);
  is_signaled_ = true;
  signal_id_++;
  cv_.notify_all();
}

void ManualResetWaitableEvent::Reset() {
  std::scoped_lock lock(mutex_);
  is_signaled_ = false;
}

void ManualResetWaitableEvent::Wait() {
  std::unique_lock lock(mutex_);

  auto last_signal_id = signal_id_;
  do {
    cv_.wait(lock);
  } while (signal_id_ == last_signal_id);
}

template <typename ConditionFn>
bool WaitWithTimeoutImpl(std::unique_lock<std::mutex>* lock,
                         std::condition_variable* cv,
                         ConditionFn condition,
                         TimeDelta timeout) {
  REZERO_DCHECK(lock->owns_lock());

  if (condition()) {
    return false;
  }

  TimeDelta wait_remaining = timeout;
  TimePoint start = TimePoint::Now();
  while (true) {
    if (std::cv_status::timeout ==
        cv->wait_for(*lock, std::chrono::nanoseconds(wait_remaining.ToNanoseconds()))) {
      return true;
    }

    if (condition()) {
      return false;
    }

    TimePoint now = TimePoint::Now();
    REZERO_DCHECK(now >= start);
    TimeDelta elapsed = now - start;
    if (elapsed >= timeout) {
      return true;
    }

    wait_remaining = timeout - elapsed;
  }
}

bool ManualResetWaitableEvent::WaitWithTimeout(TimeDelta timeout) {
  std::unique_lock lock(mutex_);

  auto last_signal_id = signal_id_;
  bool rv = WaitWithTimeoutImpl(
      &lock, &cv_,
      [this, last_signal_id]() {
        return is_signaled_ || signal_id_ != last_signal_id;
      },
      timeout);
  REZERO_DCHECK(rv || is_signaled_ || signal_id_ != last_signal_id);
  return rv;
}

} // namespace rezero