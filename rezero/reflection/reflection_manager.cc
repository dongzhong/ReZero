// Created by Dong Zhong on 2021/11/25.

#include "rezero/reflection/reflection_manager_impl.h"

#include <mutex>

namespace rezero {

static std::once_flag g_reflection_manager_init_flag;
ReflectionManager* ReflectionManager::instance_ = nullptr;

ReflectionManager* ReflectionManager::Instance() {
  std::call_once(g_reflection_manager_init_flag,
                 []() { instance_ = new ReflectionManager(); });
  return instance_;
}

ReflectionManager::ReflectionManager() = default;

} // namespace rezero
