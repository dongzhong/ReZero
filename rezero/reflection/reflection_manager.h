// Created by Dong Zhong on 2021/11/25.

#ifndef REZERO_REFLECTION_REFLECTION_MANAGER_H_
#define REZERO_REFLECTION_REFLECTION_MANAGER_H_

#include "rezero/base/macros.h"

namespace rezero {

class ReflectionManager {
 public:
  static ReflectionManager* Instance();

 private:
  ReflectionManager();

  static ReflectionManager* instance_;

  REZERO_DISALLOW_COPY_AND_ASSIGN(ReflectionManager);
};

} // namespace rezero

#endif // REZERO_REFLECTION_REFLECTION_MANAGER_H_
