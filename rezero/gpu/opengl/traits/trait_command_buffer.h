// Created by Dong Zhong on 2021/10/28.

#ifndef REZERO_GPU_OPENGL_TRAITS_TRAIT_COMMAND_BUFFER_H_
#define REZERO_GPU_OPENGL_TRAITS_TRAIT_COMMAND_BUFFER_H_

#include <map>
#include <vector>

#include "rezero/gpu/opengl/includes.h"
#include "rezero/gpu/types.h"

namespace rezero {
namespace gpu {

namespace opengl {

class CommandBufferGL : public std::enable_shared_from_this<CommandBufferGL> {
 public:
  CommandBufferGL();
  ~CommandBufferGL();

  void AddNewRenderPass(std::size_t id, const std::shared_ptr<RenderPass>& render_pass);

  std::size_t GetCurrentRenderPassId();

  void RenderPassReady(std::size_t render_pass_id);

  void CommitAllReadyRenderPasses();

 private:
  std::map<std::size_t, std::shared_ptr<RenderPass>> render_passes_;
  std::vector<std::size_t> ready_render_passes_;

  std::size_t current_render_pass_id_ = 0;

  REZERO_DISALLOW_COPY_AND_ASSIGN(CommandBufferGL);
};

} // namespace opengl

template <>
struct ImplType<CommandBuffer> {
  using type = opengl::CommandBufferGL;
};

} // namespace gpu
} // namespace rezero

#endif // REZERO_GPU_OPENGL_TRAITS_TRAIT_COMMAND_BUFFER_H_
