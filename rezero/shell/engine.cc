// Created by Dong Zhong on 2021/09/13.

#include "rezero/shell/engine.h"

#include "rezero/base/logging.h"
#include "rezero/base/message_loop.h"

namespace rezero {
namespace shell {

Engine::Engine() {
  MessageLoop::EnsureInitializedForCurrentThread();
  main_thread_ = std::make_unique<Thread>("ReZero.Main");

  task_runners_ = std::make_shared<TaskRunners>(MessageLoop::GetCurrent().GetTaskRunner(),
                                                main_thread_->GetTaskRunner());
}

Engine::~Engine() {
  // Running in platform thread
  REZERO_DCHECK(GetPlatformTaskRunner()->RunTasksOnCurrentThread());

  task_runners_.reset();
  main_thread_.reset();
}

std::shared_ptr<TaskRunner> Engine::GetPlatformTaskRunner() const {
  return task_runners_->GetPlatformTaskRunner();
}

std::shared_ptr<TaskRunner> Engine::GetMainTaskRunner() const {
  return task_runners_->GetMainTaskRunner();
}

std::shared_ptr<TaskRunners> Engine::GetTaskRunners() const {
  return task_runners_;
}

void Engine::SetPlatformView(const std::shared_ptr<PlatformView>& platform_view) {
  platform_view_ = platform_view;
}

} // namespace shell
} // namespace rezero