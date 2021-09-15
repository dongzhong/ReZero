// Created by Dong Zhong on 2021/09/14.

#include "rezero/base/message_loop_impl.h"

#include "rezero/base/build_config.h"
#if defined(REZERO_PLATFORM_ANDROID)
#include "rezero/base/android/message_loop_android.h"
#elif defined(REZERO_PLATFORM_IOS)
#include "rezero/base/ios/message_loop_ios.h"
#endif // defined(REZERO_PLATFORM_ANDROID)

#include "rezero/base/logging.h"

namespace rezero {

std::shared_ptr<MessageLoopImpl> MessageLoopImpl::Create() {
#if defined(REZERO_PLATFORM_ANDROID)
  return std::make_shared<MessageLoopAndroid>();
#elif defined(REZERO_PLATFORM_IOS)
  return std::make_shared<MessageLoopIos>();
#else
  return nullptr;
#endif // defined(REZERO_PLATFORM_ANDROID)
}

MessageLoopImpl::MessageLoopImpl()
    : task_order_(0), terminated_(false) {}

MessageLoopImpl::~MessageLoopImpl() {}

void MessageLoopImpl::PostTask(const Closure& task, TimePoint target_time) {
  REZERO_DCHECK(task != nullptr);
  if (terminated_) {
    return;
  }

  std::scoped_lock lock(queue_mutex_);
  delayed_task_queue_.push({task_order_++, task, target_time});

  WakeUp(delayed_task_queue_.top().GetTargetTime());
}

void MessageLoopImpl::DoRun() {
  if (terminated_) {
    return;
  }

  Run();

  terminated_ = true;

  RunExpiredTasksNow();

  std::scoped_lock lock(queue_mutex_);
  delayed_task_queue_ = {};
}

void MessageLoopImpl::DoTerminate() {
  terminated_ = true;
  Terminate();
}

void MessageLoopImpl::RunExpiredTasksNow() {
  const TimePoint now = TimePoint::Now();
  Closure invocatoin;
  do {
    invocatoin = GetNextTask(now);
    if (!invocatoin) {
      break;
    }

    invocatoin();
  } while (invocatoin);

  WakeUp(delayed_task_queue_.empty() ? TimePoint::Max()
                                     : delayed_task_queue_.top().GetTargetTime());
}

Closure MessageLoopImpl::GetNextTask(TimePoint target_time) {
  std::lock_guard guard(queue_mutex_);
  if (delayed_task_queue_.empty()) {
    return nullptr;
  }

  auto& delayed_task = delayed_task_queue_.top();
  if (delayed_task.GetTargetTime() > target_time) {
    return nullptr;
  }

  auto task = delayed_task.GetTask();
  delayed_task_queue_.pop();
  return task;
}

} // namespace rezero
