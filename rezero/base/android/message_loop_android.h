// Created by Dong Zhong on 2021/09/14.

#ifndef REZERO_BASE_ANDROID_MESSAGE_LOOP_ANDROID_H
#define REZERO_BASE_ANDROID_MESSAGE_LOOP_ANDROID_H

#include <android/looper.h>

#include "rezero/base/message_loop_impl.h"
#include "rezero/base/unique_fd.h"

namespace rezero {

struct UniqueLoopTraits {
  static ALooper* InvalidValue() { return nullptr; }
  static bool IsValid(ALooper* looper) { return looper != nullptr; }
  static void Free(ALooper* looper) { ::ALooper_release(looper); }
};

class MessageLoopAndroid final : public MessageLoopImpl {
 public:
  MessageLoopAndroid();
  ~MessageLoopAndroid() override;

  void Run() override;

  void Terminate() override;

  void WakeUp(TimePoint time) override;

 private:
  void OnEventFired();

  UniqueObject<ALooper*, UniqueLoopTraits> looper_;
  UniqueFD timer_fd_;
  bool running_;

  REZERO_DISALLOW_COPY_AND_ASSIGN(MessageLoopAndroid);
};

} // namespace rezero

#endif //REZERO_BASE_ANDROID_MESSAGE_LOOP_ANDROID_H
