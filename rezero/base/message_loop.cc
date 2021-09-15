// Created by Dong Zhong on 2021/09/14.

#include "rezero/base/message_loop.h"

#include "rezero/base/logging.h"
#include "rezero/base/message_loop_impl.h"
#include "rezero/base/thread_local.h"

namespace rezero {

static ThreadLocalUniquePtr<MessageLoop> tls_message_loop;

void MessageLoop::EnsureInitializedForCurrentThread() {
  if (tls_message_loop.get() != nullptr) {
    return;
  }
  tls_message_loop.reset(new MessageLoop());
}

bool MessageLoop::IsInitializedForCurrentThread() {
  return tls_message_loop.get() != nullptr;
}

MessageLoop& MessageLoop::GetCurrent() {
  auto* loop = tls_message_loop.get();
  REZERO_CHECK(loop != nullptr)
      << "MessageLoop::EnsureInitializedForCurrentThread was not called on "
         "this thread prior to message loop use.";
  return *loop;
}

MessageLoop::MessageLoop()
    : message_loop_(MessageLoopImpl::Create()),
      task_runner_(std::make_shared<TaskRunner>(message_loop_)) {
  REZERO_CHECK(message_loop_);
  REZERO_CHECK(task_runner_);
}

MessageLoop::~MessageLoop() = default;

void MessageLoop::Run() {
  message_loop_->Run();
}

void MessageLoop::Terminate() {
  message_loop_->Terminate();
}

void MessageLoop::RunExpiredTasks() {
  message_loop_->RunExpiredTasksNow();
}

std::shared_ptr<TaskRunner> MessageLoop::GetTaskRunner() const {
  return task_runner_;
}

std::shared_ptr<MessageLoopImpl> MessageLoop::GetLoopImpl() const {
  return message_loop_;
}

} // namespace rezero
