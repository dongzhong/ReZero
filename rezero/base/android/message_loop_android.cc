// Created by Dong Zhong on 2021/09/14.

#include "rezero/base/android/message_loop_android.h"

#include <fcntl.h>
#include <unistd.h>

#include "rezero/base/android/timer_fd.h"

namespace rezero {

static constexpr int kClockType = CLOCK_MONOTONIC;

static ALooper* AcquireLooperForThread() {
  ALooper* looper = ALooper_forThread();

  if (looper == nullptr) {
    looper = ALooper_prepare(0);
  }

  ALooper_acquire(looper);
  return looper;
}

MessageLoopAndroid::MessageLoopAndroid()
    : looper_(AcquireLooperForThread()),
      timer_fd_(::timerfd_create(kClockType, TFD_NONBLOCK | TFD_CLOEXEC)),
      running_(false) {
  REZERO_CHECK(looper_.is_valid());
  REZERO_CHECK(timer_fd_.is_valid());

  static const int kWakeEvents = ALOOPER_EVENT_INPUT;

  ALooper_callbackFunc read_event_fd = [](int, int events, void* data) -> int {
    if (events & kWakeEvents) {
      reinterpret_cast<MessageLoopAndroid*>(data)->OnEventFired();
    }
    return 1;
  };

  int add_result = ::ALooper_addFd(looper_.get(),
                                   timer_fd_.get(),
                                   ALOOPER_POLL_CALLBACK,
                                   kWakeEvents,
                                   read_event_fd,
                                   this);
  REZERO_CHECK(add_result == 1);
}

MessageLoopAndroid::~MessageLoopAndroid() {
  int remove_result = ::ALooper_removeFd(looper_.get(), timer_fd_.get());
  REZERO_CHECK(remove_result == 1);
}

void MessageLoopAndroid::Run() {
  REZERO_DCHECK(looper_.get() == ALooper_forThread());

  running_ = true;

  while (running_) {
    int result = ::ALooper_pollOnce(-1,
                                    nullptr,
                                    nullptr,
                                    nullptr);
    if (result == ALOOPER_POLL_TIMEOUT || result == ALOOPER_POLL_ERROR) {
      running_ = false;
    }
  }
}

void MessageLoopAndroid::Terminate() {
  running_ = false;
  ALooper_wake(looper_.get());
}

void MessageLoopAndroid::WakeUp(TimePoint time) {
  bool result = TimerRearm(timer_fd_.get(), time);
  REZERO_DCHECK(result);
}

void MessageLoopAndroid::OnEventFired() {
  if (TimerDrain(timer_fd_.get())) {
    RunExpiredTasksNow();
  }
}

} // namespace rezero