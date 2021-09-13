// Created by Dong Zhong on 2021/09/13.

#ifndef REZERO_SHELL_ENGINE_H_
#define REZERO_SHELL_ENGINE_H_

#include "rezero/base/macros.h"

namespace rezero {
namespace shell {

class Engine {
 public:
  Engine();
  virtual ~Engine();

  REZERO_DISALLOW_COPY_AND_ASSIGN(Engine);
};

} // namespace shell
} // namespace rezero

#endif // REZERO_SHELL_ENGINE_H_