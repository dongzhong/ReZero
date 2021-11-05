// Created by Dong Zhong on 2021/11/05.

#ifndef REZERO_GPU_RENDER_PASS_DESCRIPTOR_H_
#define REZERO_GPU_RENDER_PASS_DESCRIPTOR_H_

#include <array>

#include "rezero/gpu/texture.h"

namespace rezero {
namespace gpu {

struct RenderPassDescriptor {
  RenderPassDescriptor& operator=(const RenderPassDescriptor& other);

  bool need_clear_color = false;
  bool need_clear_depth = false;
  bool need_clear_stencil = false;

  std::array<float, 4> clear_color_value { { 0.0f, 0.0f, 0.0f, 0.0f } };
  float clear_depth_value = 0.0f;
  float clear_stencil_value = 0.0f;

  bool need_color_attachment = false;
  bool enable_depth_test = false;
  bool enable_stencil_test = false;

  std::shared_ptr<Texture> color_attachment_texture_ = nullptr;
  std::shared_ptr<Texture> depth_attachment_texture_ = nullptr;
  std::shared_ptr<Texture> stencil_attachment_texture_ = nullptr;
};

} // namespace gpu
} // namespace rezero

#endif // REZERO_GPU_RENDER_PASS_DESCRIPTOR_H_
