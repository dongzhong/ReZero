// Created by Dong Zhong on 2021/09/14.

#ifndef REZERO_BASE_IOS_MESSAGE_LOOP_IOS_H_
#define REZERO_BASE_IOS_MESSAGE_LOOP_IOS_H_

#include "rezero/base/message_loop_impl.h"

#include <atomic>

#include "rezero/base/ios/cf_utils.h"

namespace rezero {

class MessageLoopIos final : public MessageLoopImpl {
 public:
  MessageLoopIos();
  ~MessageLoopIos() override;

  void Run() override;

  void Terminate() override;

  void WakeUp(TimePoint time) override;

  static void OnTimerFire(CFRunLoopTimerRef timer, MessageLoopIos* loop);

 private:
  std::atomic_bool running_;
  CFRef<CFRunLoopTimerRef> delayed_wake_timer_;
  CFRef<CFRunLoopRef> loop_;

  REZERO_DISALLOW_COPY_AND_ASSIGN(MessageLoopIos);
};

} // namespace rezero

#endif // REZERO_BASE_IOS_MESSAGE_LOOP_IOS_H_
