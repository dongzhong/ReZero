// Created by Dong Zhong on 2021/11/15.

#ifndef REZERO_GPU_BUFFER_H_
#define REZERO_GPU_BUFFER_H_

#include <cstddef>

#include "rezero/base/macros.h"
#include "rezero/gpu/enums.h"

namespace rezero {
namespace gpu {

class Buffer {
 public:
  Buffer(BufferType type, BufferUsage usage, std::size_t size);
  virtual ~Buffer();

  virtual void UpdateData(void* data, std::size_t size) = 0;

  virtual void UdpateSubData(void* data, std::size_t offset, std::size_t size) = 0;

  std::size_t GetSize() const { return size_; }

  BufferType GetType() const { return type_; }

 protected:
  BufferType type_ = BufferType::kVertex;
  BufferUsage usage_ = BufferUsage::kStatic;
  std::size_t size_ = 0;

 private:
  REZERO_DISALLOW_COPY_AND_ASSIGN(Buffer);
};

} // namespace gpu
} // namespace rezero

#endif // REZERO_GPU_BUFFER_H_
