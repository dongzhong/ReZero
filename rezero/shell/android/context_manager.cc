// Created by Dong Zhong on 2021/09/26.

#include "rezero/shell/android/context_manager.h"

namespace rezero {
namespace shell {

ContextManager::ContextManager(RenderingAPI rendering_api)
    : rendering_api_(rendering_api) {}

ContextManager::~ContextManager() = default;

} // namespace shell
} // namespace rezero