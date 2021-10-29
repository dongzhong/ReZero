// Created by Dong Zhong on 2021/10/28.

#include "rezero/gpu/texture.h"

#include "rezero/base/logging.h"

namespace rezero {
namespace gpu {

Texture::Texture() {
  glGenTextures(1, &texture_.texture_name_);
  REZERO_DCHECK(texture_.texture_name_ > 0);
}

Texture::~Texture() {
  if (texture_.texture_name_ > 0) {
    glDeleteBuffers(1, &texture_.texture_name_);
    texture_.texture_name_ = 0;
  }
}

} // namespace gpu
} // namespace rezero
