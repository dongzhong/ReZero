// Created by Dong Zhong on 2021/10/28.

#ifndef REZERO_GPU_TEXTURE_H_
#define REZERO_GPU_TEXTURE_H_

#include "rezero/gpu/defines.h"
#include REZERO_GPU_BACKEND(texture.h)

namespace rezero {
namespace gpu {

class Texture {
 public:
  Texture();
  ~Texture();

 private:
  using InternalTexture = ImplType<Texture>::type;
  InternalTexture texture_;

  REZERO_DISALLOW_COPY_AND_ASSIGN(Texture);
};

} // namespace gpu
} // namespace rezero

#endif // REZERO_GPU_TEXTURE_H_
