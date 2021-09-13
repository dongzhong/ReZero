// Created by Dong Zhong on 2021/09/13.

#include "rezero/shell/ios/engine_ios.h"

namespace rezero {
namespace shell {

std::unique_ptr<EngineIos> EngineIos::Create() {
  return std::make_unique<EngineIos>();
}

EngineIos::EngineIos() = default;

EngineIos::~EngineIos() = default;

} // namespace shell
} // namespace rezero