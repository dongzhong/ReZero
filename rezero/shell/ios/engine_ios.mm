// Created by Dong Zhong on 2021/09/13.

#include "rezero/shell/ios/engine_ios.h"

#include "rezero/shell/ios/platform_view_ios.h"

namespace rezero {
namespace shell {

std::unique_ptr<EngineIos> EngineIos::Create(CALayer* layer) {
  auto engine = std::make_unique<EngineIos>();
  auto platform_view =
      std::make_shared<PlatformViewIos>(engine->GetTaskRunners(),
                                        scoped_nsobject<CALayer>{[layer retain]});
  engine->SetPlatformView(platform_view);
  return engine;
}

EngineIos::EngineIos() = default;

EngineIos::~EngineIos() = default;

void EngineIos::Resume() {
  platform_view_->Resume();
}

void EngineIos::Pause() {
  platform_view_->Pause();
}

void EngineIos::UpdateDrawableSize() {
  std::dynamic_pointer_cast<PlatformViewIos>(platform_view_)->UpdateStorageSizeIfNecessary();
}

} // namespace shell
} // namespace rezero
