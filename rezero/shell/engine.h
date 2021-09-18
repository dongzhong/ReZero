// Created by Dong Zhong on 2021/09/13.

#ifndef REZERO_SHELL_ENGINE_H_
#define REZERO_SHELL_ENGINE_H_

#include "rezero/base/macros.h"
#include "rezero/base/thread.h"
#include "rezero/shell/platform_view.h"

namespace rezero {
namespace shell {

class Engine {
 public:
  Engine();
  virtual ~Engine();

  std::shared_ptr<TaskRunner> GetPlatformTaskRunner() const { return platform_task_runner_; }

  std::shared_ptr<TaskRunner> GetMainTaskRunner() const { return main_thread_->GetTaskRunner(); }

  void SetPlatformView(const std::shared_ptr<PlatformView>& platform_view);

 private:
  std::unique_ptr<Thread> main_thread_;
  std::shared_ptr<TaskRunner> platform_task_runner_;

  std::shared_ptr<PlatformView> platform_view_;

  REZERO_DISALLOW_COPY_AND_ASSIGN(Engine);
};

} // namespace shell
} // namespace rezero

#endif // REZERO_SHELL_ENGINE_H_