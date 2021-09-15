// Created by Dong Zhong on 2021/09/14.

#ifndef REZERO_BASE_MESSAGE_LOOP_H_
#define REZERO_BASE_MESSAGE_LOOP_H_

#include "rezero/base/task_runner.h"

namespace rezero {

class MessageLoopImpl;

class MessageLoop {
 public:
  static MessageLoop& GetCurrent();

  static void EnsureInitializedForCurrentThread();

  static bool IsInitializedForCurrentThread();

  MessageLoop();
  ~MessageLoop();

  void Run();

  void Terminate();

  void RunExpiredTasks();

  std::shared_ptr<TaskRunner> GetTaskRunner() const;

 private:
  std::shared_ptr<MessageLoopImpl> GetLoopImpl() const;

  std::shared_ptr<MessageLoopImpl> message_loop_;
  std::shared_ptr<TaskRunner> task_runner_;

  REZERO_DISALLOW_COPY_AND_ASSIGN(MessageLoop);
};

} // namespace rezero

#endif // REZERO_BASE_MESSAGE_LOOP_H_
