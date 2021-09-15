// Created by Dong Zhong on 2021/09/14.

#include "rezero/base/thread.h"

#include "rezero/base/build_config.h"
#include "rezero/base/message_loop.h"
#include "rezero/base/waitable_event.h"

namespace rezero {

void Thread::SetCurrentThreadName(const std::string& name) {
  if (name == "") {
    return;
  }

#if defined(REZERO_PLATFORM_ANDROID)
  pthread_setname_np(pthread_self(), name.c_str());
#elif defined(REZERO_PLATFROM_IOS)
  pthread_setname_np(name.c_str());
#endif // defined(REZERO_PLATFORM_ANDROID)
}

Thread::Thread(const std::string& thread_name) {
  AutoResetWaitableEvent latch;
  std::shared_ptr<TaskRunner> task_runner;

  thread_ = std::make_unique<std::thread>([&latch, &task_runner, thread_name]() -> void {
    SetCurrentThreadName(thread_name);
    MessageLoop::EnsureInitializedForCurrentThread();
    auto& loop = MessageLoop::GetCurrent();
    task_runner = loop.GetTaskRunner();
    latch.Signal();
    loop.Run();
  });
  latch.Wait();

  task_runner_ = task_runner;
}

Thread::~Thread() {
  task_runner_->PostTask([]() {
    MessageLoop::GetCurrent().Terminate();
  });
  thread_->join();
}

std::shared_ptr<TaskRunner> Thread::GetTaskRunner() const {
  return task_runner_;
}

} // namespace rezero