// Created by Dong Zhong on 2021/09/16.

#include "rezero/shell/platform_view.h"

#include "rezero/base/logging.h"

namespace rezero {
namespace shell {

PlatformView::PlatformView(const std::shared_ptr<TaskRunners>& task_runners)
    : task_runners_(task_runners) {
  REZERO_DCHECK(task_runners_);
}

PlatformView::~PlatformView() = default;

} // namespace shell
} // namespace rezero