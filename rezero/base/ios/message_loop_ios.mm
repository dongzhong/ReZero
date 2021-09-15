// Created by Dong Zhong on 2021/09/14.

#include "rezero/base/ios/message_loop_ios.h"

#import <CoreFoundation/CFRunLoop.h>

#include "rezero/base/logging.h"

namespace rezero {

static constexpr CFTimeInterval kDistantFuture = 1.0e10;

MessageLoopIos::MessageLoopIos()
    : running_(false), loop_((CFRunLoopRef)CFRetain(CFRunLoopGetCurrent())) {
  REZERO_DCHECK(loop_ != nullptr);

  CFRunLoopTimerContext timer_context = {
      .info = this,
  };
  delayed_wake_timer_.Reset(
      CFRunLoopTimerCreate(kCFAllocatorDefault, kDistantFuture, HUGE_VAL, 0, 0,
                           reinterpret_cast<CFRunLoopTimerCallBack>(&MessageLoopIos::OnTimerFire),
                           &timer_context));
  REZERO_DCHECK(delayed_wake_timer_ != nullptr);
  CFRunLoopAddTimer(loop_, delayed_wake_timer_, kCFRunLoopCommonModes);
}

MessageLoopIos::~MessageLoopIos() {
  CFRunLoopTimerInvalidate(delayed_wake_timer_);
  CFRunLoopRemoveTimer(loop_, delayed_wake_timer_, kCFRunLoopCommonModes);
}

void MessageLoopIos::Run() {
  REZERO_DCHECK(loop_ == CFRunLoopGetCurrent());

  running_ = true;

  while (running_) {
    @autoreleasepool {
      int result = CFRunLoopRunInMode(kCFRunLoopDefaultMode, kDistantFuture, YES);
      if (result == kCFRunLoopRunStopped || result == kCFRunLoopRunFinished) {
        @autoreleasepool {
          RunExpiredTasksNow();
        }
        running_ = false;
      }
    }
  }
}

void MessageLoopIos::Terminate() {
  running_ = false;
  CFRunLoopStop(loop_);
}

void MessageLoopIos::WakeUp(TimePoint time) {
  CFRunLoopTimerSetNextFireDate(
      delayed_wake_timer_,
      CFAbsoluteTimeGetCurrent() + (time - TimePoint::Now()).ToSecondsF());
}

void MessageLoopIos::OnTimerFire(CFRunLoopTimerRef timer, MessageLoopIos* loop) {
  @autoreleasepool {
    loop->RunExpiredTasksNow();
  }
}

} // namespace rezero
