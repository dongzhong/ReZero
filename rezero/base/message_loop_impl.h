// Created by Dong Zhong on 2021/09/14.

#ifndef REZERO_BASE_MESSAGE_LOOP_IMPL_H_
#define REZERO_BASE_MESSAGE_LOOP_IMPL_H_

#include <atomic>
#include <mutex>

#include "rezero/base/message_loop.h"
#include "rezero/base/delayed_task.h"

namespace rezero {

class MessageLoopImpl {
 public:
  static std::shared_ptr<MessageLoopImpl> Create();

  MessageLoopImpl();
  virtual ~MessageLoopImpl();

  virtual void Run() = 0;
  virtual void Terminate() = 0;
  virtual void WakeUp(TimePoint time) = 0;

  void PostTask(const Closure& task, TimePoint target_time);

  void DoRun();

  void DoTerminate();

 protected:
  void RunExpiredTasksNow();

  Closure GetNextTask(TimePoint target_time);

 private:
  // TODO: void FlushTasks();

  DelayedTaskQueue delayed_task_queue_;
  size_t task_order_;
  std::mutex queue_mutex_;

  std::atomic_bool terminated_;

  friend class MessageLoop;

  REZERO_DISALLOW_COPY_AND_ASSIGN(MessageLoopImpl);
};

} // namespace rezero

#endif // REZERO_BASE_MESSAGE_LOOP_IMPL_H_
