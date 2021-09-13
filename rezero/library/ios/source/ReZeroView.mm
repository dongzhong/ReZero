// Created by Dong Zhong on 2021/09/13.

#include "rezero/library/ios/include/ReZero/ReZeroView.h"

#include <memory>

#include "rezero/version.h"
#include "rezero/shell/ios/engine_ios.h"

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
  engine_ = rezero::shell::EngineIos::Create();
}

@end
