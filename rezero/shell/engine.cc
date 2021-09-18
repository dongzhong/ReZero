// Created by Dong Zhong on 2021/09/13.

#include "rezero/shell/engine.h"

#include "rezero/base/logging.h"
#include "rezero/base/message_loop.h"

namespace rezero {
namespace shell {

Engine::Engine() {
  MessageLoop::EnsureInitializedForCurrentThread();
  platform_task_runner_ = MessageLoop::GetCurrent().GetTaskRunner();

  main_thread_ = std::make_unique<Thread>("ReZero.Main");
}

Engine::~Engine() {
  // Running in platform thread
  REZERO_DCHECK(GetPlatformTaskRunner()->RunTasksOnCurrentThread());

  main_thread_.reset();
  platform_task_runner_.reset();
}

void Engine::SetPlatformView(const std::shared_ptr<PlatformView>& platform_view) {
  platform_view_ = platform_view;
}

} // namespace shell
} // namespace rezero