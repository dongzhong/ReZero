// Created by Dong Zhong on 2021/11/14.

#include "rezero/gpu/swap_chain.h"

namespace rezero {
namespace gpu {

SwapChain::SwapChain() = default;

SwapChain::~SwapChain() = default;

void SwapChain::SetValid(bool valid) {
  is_valid_ = valid;
}

void SwapChain::SetSize(const std::array<int, 2>& size) {
  size_ = size;
}

} // namespace gpu
} // namespace rezero
