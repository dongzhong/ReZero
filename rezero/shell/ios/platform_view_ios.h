// Created by Dong Zhong on 2021/09/17.

#ifndef REZERO_SHELL_IOS_PLATFORM_VIEW_IOS_H_
#define REZERO_SHELL_IOS_PLATFORM_VIEW_IOS_H_

#include "rezero/base/ios/scoped_nsobject.h"
#include "rezero/shell/ios/context_manager.h"
#include "rezero/shell/platform_view.h"

#import <QuartzCore/CALayer.h>

namespace rezero {
namespace shell {

class PlatformViewIos final : public PlatformView {
 public:
  PlatformViewIos(const std::shared_ptr<TaskRunners>& task_runners,
                  const scoped_nsobject<CALayer>& layer);
  ~PlatformViewIos() override;

  bool UpdateStorageSizeIfNecessary();

 private:
  bool Present() override;

  scoped_nsobject<CALayer> layer_;
  std::unique_ptr<ContextManager> context_manager_;

  REZERO_DISALLOW_COPY_AND_ASSIGN(PlatformViewIos);
};

} // namespace shell
} // namespace rezero

#endif // REZERO_SHELL_IOS_PLATFORM_VIEW_IOS_H_
