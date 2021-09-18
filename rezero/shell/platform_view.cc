// Created by Dong Zhong on 2021/09/16.

#include "rezero/shell/platform_view.h"

#include "rezero/base/logging.h"

namespace rezero {
namespace shell {

PlatformView::PlatformView(const std::shared_ptr<TaskRunner>& main_task_runner)
    : main_task_runner_(main_task_runner) {
  REZERO_DCHECK(main_task_runner_);
}

PlatformView::~PlatformView() = default;

} // namespace shell
} // namespace rezero