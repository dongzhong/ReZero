// Created by Dong Zhong on 2021/10/28.

#ifndef REZERO_GPU_BUFFER_H_
#define REZERO_GPU_BUFFER_H_

#include <cstddef>

#include "rezero/gpu/defines.h"
#include REZERO_GPU_BACKEND(buffer.h)

namespace rezero {
namespace gpu {

class Buffer {
 public:
  using InternalBuffer = ImplType<Buffer>::type;

  Buffer(std::size_t size, BufferType type, BufferUsage usage);
  ~Buffer();

  void UpdateData(std::size_t size, const void* data);

  void UpdateSubData(std::size_t offset, std::size_t size, const void* data);

  const InternalBuffer& GetInterlnalBuffer() const { return buffer_; }

  BufferType GetBufferType() const { return type_; }

 private:
  InternalBuffer buffer_;

  std::size_t size_ = 0;
  BufferType type_ = BufferType::kVertex;
  BufferUsage usage_ = BufferUsage::kStatic;

  REZERO_DISALLOW_COPY_AND_ASSIGN(Buffer);
};

} // namespace gpu
} // namespace rezero

#endif // REZERO_GPU_BUFFER_H_
