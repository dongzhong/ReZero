// Created by Dong Zhong on 2021/09/13.

#ifndef REZERO_SHELL_ENGINE_H_
#define REZERO_SHELL_ENGINE_H_

#include "rezero/base/macros.h"
#include "rezero/base/task_runners.h"
#include "rezero/base/thread.h"
#include "rezero/shell/platform_view.h"

namespace rezero {
namespace shell {

class Engine {
 public:
  Engine();
  virtual ~Engine();

  std::shared_ptr<TaskRunner> GetPlatformTaskRunner() const;

  std::shared_ptr<TaskRunner> GetMainTaskRunner() const;

  std::shared_ptr<TaskRunners> GetTaskRunners() const;

  void SetPlatformView(const std::shared_ptr<PlatformView>& platform_view);

 protected:
  std::shared_ptr<PlatformView> platform_view_;

 private:
  std::unique_ptr<Thread> main_thread_;

  std::shared_ptr<TaskRunners> task_runners_;

  REZERO_DISALLOW_COPY_AND_ASSIGN(Engine);
};

} // namespace shell
} // namespace rezero

#endif // REZERO_SHELL_ENGINE_H_
