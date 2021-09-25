// Created by Dong Zhong on 2021/09/13.

#include "rezero/library/ios/include/ReZero/ReZeroView.h"

#include <memory>

#include "rezero/version.h"
#include "rezero/shell/ios/engine_ios.h"
#include "rezero/shell/ios/rendering_api_selection.h"

#include "rezero/base/logging.h"

using namespace rezero;

@implementation ReZeroView {
  std::unique_ptr<rezero::shell::EngineIos> engine_;
}

+ (NSString*)getVersion {
  return [NSString stringWithCString:rezero::kVersion
                            encoding:[NSString defaultCStringEncoding]];
}

- (instancetype)initWithFrame:(CGRect)frame {
  self = [super initWithFrame:frame];
  if (self) {
    [self commonInit];
  }
  return self;
}

- (instancetype)initWithCoder:(NSCoder *)coder {
  self = [super initWithCoder:coder];
  if (self) {
    [self commonInit];
  }
  return self;
}

- (void)commonInit {
  engine_ = rezero::shell::EngineIos::Create([self layer]);

  REZERO_DCHECK(engine_);
  [self setupNotificationObserver];
}

+ (Class)layerClass {
  return rezero::shell::GetCALayerClassForRenderingApi(
      rezero::shell::GetRenderingApiForProcess());
}

- (void)setupNotificationObserver {
  NSNotificationCenter* center = [NSNotificationCenter defaultCenter];

  [center addObserver:self
             selector:@selector(applicationWillResignActive:)
                 name:UIApplicationWillResignActiveNotification
               object:nil];

  [center addObserver:self
             selector:@selector(applicationDidEnterBackground:)
                 name:UIApplicationDidEnterBackgroundNotification
               object:nil];

  [center addObserver:self
             selector:@selector(applicationWillEnterForeground:)
                 name:UIApplicationWillEnterForegroundNotification
               object:nil];

  [center addObserver:self
             selector:@selector(applicationDidBecomeActive:)
                 name:UIApplicationDidBecomeActiveNotification
               object:nil];
}

- (void)applicationWillResignActive:(NSNotification*)notification {
  [self updateRunningState];
}

- (void)applicationDidEnterBackground:(NSNotification*)notification {
  [self updateRunningState];
}

- (void)applicationWillEnterForeground:(NSNotification*)notification {
  [self updateRunningState];
}

- (void)applicationDidBecomeActive:(NSNotification*)notification {
  [self updateRunningState];
}

- (void)updateRunningState {
  UIApplicationState state = [UIApplication sharedApplication].applicationState;
  if (state == UIApplicationStateActive && self.window) {
    engine_->Resume();
  } else {
    engine_->Pause();
  }
}

@end
