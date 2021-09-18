// Created by Dong Zhong on 2021/09/16.

#ifndef REZERO_SHELL_PLATFORM_VIEW_H_
#define REZERO_SHELL_PLATFORM_VIEW_H_

#include "rezero/base/macros.h"
#include "rezero/base/task_runner.h"

namespace rezero {
namespace shell {

class PlatformView {
 public:
  PlatformView(const std::shared_ptr<TaskRunner>& main_task_runner);
  virtual ~PlatformView();

 protected:
  std::shared_ptr<TaskRunner> main_task_runner_;

  REZERO_DISALLOW_COPY_AND_ASSIGN(PlatformView);
};

} // namespace shell
} // namespace rezero

#endif // REZERO_SHELL_PLATFORM_VIEW_H_