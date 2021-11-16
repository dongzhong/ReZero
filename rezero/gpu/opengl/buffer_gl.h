// Created by Dong Zhong on 2021/11/15.

#ifndef REZERO_GPU_OPENGL_BUFFER_GL_H_
#define REZERO_GPU_OPENGL_BUFFER_GL_H_

#include "rezero/gpu/buffer.h"
#include "rezero/gpu/opengl/includes_gl.h"

namespace rezero {
namespace gpu {

class BufferGL final : public Buffer {
 public:
  BufferGL(BufferType type, BufferUsage usage, std::size_t size);
  ~BufferGL() override;

  void UpdateData(void* data, std::size_t size) override;

  void UdpateSubData(void* data, std::size_t offset, std::size_t size) override;

  GLuint GetBufferName() const { return buffer_name_; }
  GLenum GetBufferType() const { return buffer_type_; }

 private:
  GLenum buffer_type_ = GL_ARRAY_BUFFER;
  GLenum buffer_usage_ = GL_STATIC_DRAW;

  GLuint buffer_name_;
  std::size_t allocated_size_ = 0;

  REZERO_DISALLOW_COPY_AND_ASSIGN(BufferGL);
};

} // namespace gpu
} // namespace rezero

#endif // REZERO_GPU_OPENGL_BUFFER_GL_H_
