// Created by Dong Zhong on 2021/09/21.

#ifndef REZERO_SHELL_IOS_VSYNC_WAITER_IOS_H_
#define REZERO_SHELL_IOS_VSYNC_WAITER_IOS_H_

#include "rezero/base/ios/scoped_nsobject.h"
#include "rezero/shell/vsync_waiter.h"

@interface VsyncClient : NSObject

- (instancetype)initWithTaskRunner:(std::shared_ptr<rezero::TaskRunner>)taskRunner
                          callback:(rezero::shell::VsyncWaiter::Callback)callback;

- (void)await;

- (void)invalidate;

@end

namespace rezero {
namespace shell {

class VsyncWaiterIos final : public VsyncWaiter {
 public:
  VsyncWaiterIos(const std::shared_ptr<TaskRunners>& task_runners);
  ~VsyncWaiterIos() override;

 protected:
  void AwaitVsync() override;

 private:
  scoped_nsobject<VsyncClient> client_;

  REZERO_DISALLOW_COPY_AND_ASSIGN(VsyncWaiterIos);
};

} // namespace shell
} // namespace rezero

#endif // REZERO_SHELL_IOS_VSYNC_WAITER_IOS_H_
