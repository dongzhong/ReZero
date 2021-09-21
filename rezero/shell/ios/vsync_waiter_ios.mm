// Created by Dong Zhong on 2021/09/21.

#include "rezero/shell/ios/vsync_waiter_ios.h"

#include "rezero/base/logging.h"

#import <QuartzCore/CADisplayLink.h>
#import <UIKit/UIKit.h>

@implementation VsyncClient {
  rezero::shell::VsyncWaiter::Callback callback_;
  rezero::scoped_nsobject<CADisplayLink> display_link_;
}

- (instancetype)initWithTaskRunner:(std::shared_ptr<rezero::TaskRunner>)taskRunner
                          callback:(rezero::shell::VsyncWaiter::Callback)callback {
  self = [super init];

  if (self) {
    callback_ = std::move(callback);
    display_link_ = rezero::scoped_nsobject<CADisplayLink> {
        [[CADisplayLink displayLinkWithTarget:self selector:@selector(onDisplayLink:)] retain]
    };
    display_link_.get().paused = YES;

    taskRunner->PostTask([client = [self retain]]() {
      [client->display_link_.get() addToRunLoop:[NSRunLoop currentRunLoop]
                                        forMode:NSRunLoopCommonModes];
      [client release];
    });
  }

  return self;
}

- (void)await {
  display_link_.get().paused = NO;
}

- (void)invalidate {
  [display_link_.get() invalidate];
}

- (void)onDisplayLink:(CADisplayLink*)link {
  CFTimeInterval delay = CACurrentMediaTime() - link.timestamp;

  rezero::TimePoint start_time = rezero::TimePoint::Now() - rezero::TimeDelta::FromSecondsF(delay);
  rezero::TimePoint end_time = start_time + rezero::TimeDelta::FromSecondsF(link.duration);

  display_link_.get().paused = YES;

  callback_(start_time, end_time);
}

- (void)dealloc {
  [self invalidate];

  [super dealloc];
}

@end

namespace rezero {
namespace shell {

VsyncWaiterIos::VsyncWaiterIos(const std::shared_ptr<TaskRunners>& task_runners)
    : VsyncWaiter(task_runners),
      client_([[VsyncClient alloc] initWithTaskRunner:task_runners_->GetMainTaskRunner()
                                             callback:std::bind(&VsyncWaiterIos::FireCallback,
                                                                this,
                                                                std::placeholders::_1,
                                                                std::placeholders::_2)]) {}

VsyncWaiterIos::~VsyncWaiterIos() {
  [client_ invalidate];
}

void VsyncWaiterIos::AwaitVsync() {
  [client_ await];
}

} // namespace shell
} // namespace rezero
