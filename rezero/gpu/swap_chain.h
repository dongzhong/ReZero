// Created by Dong Zhong on 2021/11/14.

#ifndef REZERO_GPU_SWAP_CHAIN_H_
#define REZERO_GPU_SWAP_CHAIN_H_

#include <array>

#include "rezero/base/macros.h"

namespace rezero {
namespace gpu {

class SwapChain {
 public:
  SwapChain();
  virtual ~SwapChain();

  void SetValid(bool valid);
  bool IsValid() const { return is_valid_; }

  std::array<int, 2> GetSize() { return size_; }
  void SetSize(const std::array<int, 2>& size);

 protected:
  bool is_valid_ = false;

  std::array<int, 2> size_;

 private:
  REZERO_DISALLOW_COPY_AND_ASSIGN(SwapChain);
};

} // namespace gpu
} // namespace rezero

#endif // REZERO_GPU_SWAP_CHAIN_H_
