// Created by Dong Zhong on 2021/11/03.

#ifndef REZERO_GPU_OPENGL_TRAITS_TRAIT_RENDER_PASS_H_
#define REZERO_GPU_OPENGL_TRAITS_TRAIT_RENDER_PASS_H_

#include "rezero/gpu/opengl/includes.h"
#include "rezero/gpu/types.h"

namespace rezero {
namespace gpu {

namespace opengl {

using EndRenderPassCallback = std::function<void(std::size_t)>;

class RenderPassGL {
 public:
  RenderPassGL();
  ~RenderPassGL();

  void SetRenderPassId(std::size_t id);

  void SetEndRenderPassCallback(const EndRenderPassCallback& callback);

  std::size_t GetRenderPassId() const { return render_pass_id_; }

  void EndRenderPass();

  void PerformDrawing();

  // Update attributes
  void SetNeedClearColor(bool need_clear_color);
  void SetNeedClearDepth(bool need_clear_depth);
  void SetNeedClearStencil(bool need_clear_stencil);

 private:
  void PrepareDrawing();

  std::size_t render_pass_id_ = 0;
  EndRenderPassCallback callback_ = {};

  bool need_clear_color_ = false;
  bool need_clear_depth_ = false;
  bool need_clear_stencil_ = false;

  REZERO_DISALLOW_COPY_AND_ASSIGN(RenderPassGL);
};

} // namespace opengl

template <>
struct ImplType<RenderPass> {
  using type = opengl::RenderPassGL;
};

} // namespace gpu
} // namespace rezero

#endif // REZERO_GPU_OPENGL_TRAITS_TRAIT_RENDER_PASS_H_
