// Created by Dong Zhong on 2021/09/13.

#include "rezero/library/ios/include/ReZero/ReZeroView.h"

#include <memory>

#include "rezero/version.h"
#include "rezero/shell/ios/engine_ios.h"

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

- (void)viewDidMoveToWindow {
  if (self.window) {
    engine_->Resume();
  } else {
    engine_->Pause();
  }
}

+ (Class)layerClass {
  return [CAEAGLLayer class];
}

- (void)layoutSubviews {
  UIScreen* current_screen = nil;
  if (@available(iOS 13.0, *)) {
    current_screen = self.window.windowScene.screen;
  } else {
    current_screen = self.window.screen;
  }
  CGFloat contents_scale = current_screen.nativeScale;
  if (contents_scale <= 0) {
    contents_scale = UIScreen.mainScreen.nativeScale;
  }
  contents_scale = contents_scale > 0.0f ? contents_scale : 1.0f;
  self.layer.contentsScale = contents_scale;
  self.layer.rasterizationScale = contents_scale;
  self.layer.allowsGroupOpacity = NO;

  [super layoutSubviews];

  engine_->UpdateDrawableSize();
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
