// Created by Dong Zhong on 2021/09/13.

#ifndef REZERO_SHELL_IOS_ENGINE_IOS_H_
#define REZERO_SHELL_IOS_ENGINE_IOS_H_

#include <memory>

#include "rezero/shell/engine.h"

namespace rezero {
namespace shell {

class EngineIos final : public Engine {
 public:
  static std::unique_ptr<EngineIos> Create();

  EngineIos();
  ~EngineIos() override;
};

} // namespace shell
} // namespace rezero

#endif // REZERO_SHELL_IOS_ENGINE_IOS_H_