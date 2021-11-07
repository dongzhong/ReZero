// Created by Dong Zhong on 2021/11/03.

#include "rezero/gpu/render_pass.h"

#include "rezero/base/logging.h"
#include "rezero/gpu/opengl/state_machine_gl.h"

namespace rezero {
namespace gpu {

namespace opengl {

RenderPassGL::RenderPassGL() {
  // TODO:
}

RenderPassGL::~RenderPassGL() {
  // TODO:
}

void RenderPassGL::SetRenderPassId(std::size_t id) {
  render_pass_id_ = id;
}

void RenderPassGL::SetEndRenderPassCallback(const EndRenderPassCallback& callback) {
  callback_ = callback;
}

void RenderPassGL::EndRenderPass() {
  if (callback_) {
    callback_(render_pass_id_);
  }
}

void RenderPassGL::PerformDrawing() {
  PrepareDrawing();

  if (vertex_or_index_count_ > 0) {
    switch (draw_method_) {
      case DrawMethod::kArrays:
        glDrawArrays(Utils::ToGLPrimitiveType(primitive_type_),
                     static_cast<GLint>(first_vertex_or_index_),
                     static_cast<GLsizei>(vertex_or_index_count_));
        break;
      case DrawMethod::kElements:
        glDrawElements(Utils::ToGLPrimitiveType(primitive_type_),
                       static_cast<GLsizei>(vertex_or_index_count_),
                       Utils::ToGLIndexFormat(index_format_),
                       reinterpret_cast<const GLvoid*>(first_vertex_or_index_));
        break;
      default:
        break;
    }
  }

  AfterDraw();
}

void RenderPassGL::SetRenderPassDescriptor(const RenderPassDescriptor& descriptor) {
  render_pass_descriptor_ = descriptor;
}

void RenderPassGL::SetVertexBuffer(const std::shared_ptr<Buffer>& vertex_buffer) {
  REZERO_DCHECK(vertex_buffer && (vertex_buffer->GetBufferType() == BufferType::kVertex))
      << "Vertex buffer is null or not vertex type.";
  vertex_buffer_ = vertex_buffer;
}

void RenderPassGL::SetIndexBuffer(const std::shared_ptr<Buffer>& index_buffer) {
  REZERO_DCHECK(index_buffer && (index_buffer->GetBufferType() == BufferType::kIndex))
      << "Index buffer is null or not index type.";
  index_buffer_ = index_buffer;
}

void RenderPassGL::SetDepthStencil(const DepthStencilDescriptor& descriptor) {
  enable_depth_test_ = descriptor.enable_depth_test;
  enable_stencil_test_ = descriptor.enable_stencil_test;

  depth_compare_function_ = Utils::ToGLCompareFunction(descriptor.depth_compare_function);
  depth_write_enable_ = descriptor.depth_write_enable;

  auto& front_stencil_descriptor = descriptor.front_stencil_descriptor;
  front_stencil_compare_function_ = Utils::ToGLCompareFunction(front_stencil_descriptor.stencil_compare_function);
  front_stencil_failed_operation_ = Utils::ToGLStencilOperation(front_stencil_descriptor.stencil_failed_operation);
  front_depth_failed_operation_ = Utils::ToGLStencilOperation(front_stencil_descriptor.depth_failed_operation);
  front_test_pass_operation_ = Utils::ToGLStencilOperation(front_stencil_descriptor.test_pass_operation);
  front_stencil_read_mask_ = front_stencil_descriptor.read_mask;
  front_stencil_write_mask_ = front_stencil_descriptor.write_mask;

  auto& back_stencil_descriptor = descriptor.back_stencil_descriptor;
  back_stencil_compare_function_ = Utils::ToGLCompareFunction(back_stencil_descriptor.stencil_compare_function);
  back_stencil_failed_operation_ = Utils::ToGLStencilOperation(back_stencil_descriptor.stencil_failed_operation);
  back_depth_failed_operation_ = Utils::ToGLStencilOperation(back_stencil_descriptor.depth_failed_operation);
  back_test_pass_operation_ = Utils::ToGLStencilOperation(back_stencil_descriptor.test_pass_operation);
  back_stencil_read_mask_ = back_stencil_descriptor.read_mask;
  back_stencil_write_mask_ = back_stencil_descriptor.write_mask;
}

void RenderPassGL::SetReferenceValue(unsigned int value) {
  front_reference_value_ = value;
}

void RenderPassGL::SetReferenceValue(unsigned int front_value, unsigned int back_value) {
  front_reference_value_ = front_value;
  back_reference_value_ = back_value;
}

void RenderPassGL::SetViewport(int x, int y, unsigned int width, unsigned int height) {
  viewport_.x = x;
  viewport_.y = y;
  viewport_.width = width;
  viewport_.height = height;
}

void RenderPassGL::SetScissor(int x, int y, unsigned int width, unsigned int height) {
  scissor_.x = x;
  scissor_.y = y;
  scissor_.width = width;
  scissor_.height = height;
}

void RenderPassGL::SetCullMode(CullMode mode) {
  cull_mode_ = mode;
}

void RenderPassGL::SetWindingMode(WindingMode mode) {
  winding_mode_ = mode;
}

void RenderPassGL::DrawArrays(PrimitiveType primitive_type, std::size_t start, std::size_t count) {
  draw_method_ = DrawMethod::kArrays;
  primitive_type_ = primitive_type;
  first_vertex_or_index_ = start;
  vertex_or_index_count_ = count;
}

void RenderPassGL::DrawElements(PrimitiveType primitive_type,
                                IndexFormat index_format,
                                std::size_t offset,
                                std::size_t count) {
  draw_method_ = DrawMethod::kElements;
  primitive_type_ = primitive_type;
  first_vertex_or_index_ = offset;
  vertex_or_index_count_ = count;
  index_format_ = index_format;
}

void RenderPassGL::PrepareDrawing() {
  // TODO:
  PrepareDepthStencil();
  PrepareRenderPassDescriptor();
  PrepareBuffers();

  auto& state_machine = StateMachineGL::GetCurrent();
  state_machine.SetViewport(viewport_.x,
                            viewport_.y,
                            viewport_.width,
                            viewport_.height);

  state_machine.SetScissor(scissor_.x,
                           scissor_.y,
                           scissor_.width,
                           scissor_.height);

  bool enable_cull_mode = false;
  GLenum cull_mode = GL_BACK;
  Utils::ToGLCullMode(cull_mode_, enable_cull_mode, cull_mode);
  state_machine.SetCullMode(enable_cull_mode, cull_mode);

  state_machine.SetWindingMode(Utils::ToGLWindingMode(winding_mode_));
}

void RenderPassGL::PrepareRenderPassDescriptor() {
  auto& state_machine = StateMachineGL::GetCurrent();

  bool need_color_attachment = (render_pass_descriptor_.color_attachment_texture_ != nullptr);
  bool need_depth_attachment = enable_depth_test_ &&
                               (render_pass_descriptor_.depth_attachment_texture_ != nullptr);
  bool need_stencil_attachment = enable_stencil_test_ &&
                                 (render_pass_descriptor_.stencil_attachment_texture_ != nullptr);
  if (need_color_attachment || need_depth_attachment || need_stencil_attachment) {
    origin_framebuffer_ = state_machine.GetCurrentBoundFramebuffer();
    glGenFramebuffers(1, &curren_framebuffer_);
    REZERO_DCHECK(curren_framebuffer_ > 0);
    glBindFramebuffer(GL_FRAMEBUFFER, curren_framebuffer_);
  }

  if (need_color_attachment) {
    auto internal_texture =
        render_pass_descriptor_.color_attachment_texture_->GetInteralTexture();
    glFramebufferTexture2D(GL_FRAMEBUFFER,
                           GL_COLOR_ATTACHMENT0,
                           GL_TEXTURE_2D,
                           internal_texture.texture_name_,
                           0);
  }

  if (need_depth_attachment) {
    auto internal_texture =
        render_pass_descriptor_.depth_attachment_texture_->GetInteralTexture();
    glFramebufferTexture2D(GL_FRAMEBUFFER,
                           GL_DEPTH_ATTACHMENT,
                           GL_TEXTURE_2D,
                           internal_texture.texture_name_,
                           0);
  }

  if (need_stencil_attachment) {
    auto internal_texture =
        render_pass_descriptor_.stencil_attachment_texture_->GetInteralTexture();
    glFramebufferTexture2D(GL_FRAMEBUFFER,
                           GL_STENCIL_ATTACHMENT,
                           GL_TEXTURE_2D,
                           internal_texture.texture_name_,
                           0);
  }

  if (curren_framebuffer_ > 0) {
    REZERO_DCHECK(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        << "Current framebuffer is not complete.";
  }

  CHECK_GL_ERROR_DEBUG();

  GLbitfield mask = 0;
  if (render_pass_descriptor_.need_clear_color) {
    state_machine.SetClearColorValue(render_pass_descriptor_.clear_color_value);
    mask |= GL_COLOR_BUFFER_BIT;
  }

  if (render_pass_descriptor_.need_clear_depth) {
    state_machine.SetClearDepthValue(render_pass_descriptor_.clear_depth_value);
    mask |= GL_DEPTH_BUFFER_BIT;
  }

  if (render_pass_descriptor_.need_clear_stencil) {
    state_machine.SetClearStencilValue(render_pass_descriptor_.clear_stencil_value);
    mask |= GL_STENCIL_BUFFER_BIT;
  }

  if (mask != 0) {
    glClear(mask);
  }
}

void RenderPassGL::PrepareBuffers() {
  REZERO_DCHECK(vertex_buffer_) << "No vertex buffer.";
  auto& state_machine = StateMachineGL::GetCurrent();

  auto& internal_vertex_buffer = vertex_buffer_->GetInterlnalBuffer();
  state_machine.BindBuffer(GL_ARRAY_BUFFER, internal_vertex_buffer.buffer_name_);

  if (index_buffer_) {
    auto& internal_index_buffer = index_buffer_->GetInterlnalBuffer();
    state_machine.BindBuffer(GL_ELEMENT_ARRAY_BUFFER, internal_index_buffer.buffer_name_);
  }
}

void RenderPassGL::PrepareDepthStencil() {
  auto& state_machine = StateMachineGL::GetCurrent();

  state_machine.SetDepthTest(enable_depth_test_);
  state_machine.SetDepthCompareFunction(depth_compare_function_);
  state_machine.SetDepthWriteMask(depth_write_enable_);

  state_machine.SetStencilTest(enable_stencil_test_);
  state_machine.SetFrontStencilFunction(front_stencil_compare_function_,
                                        front_reference_value_,
                                        front_stencil_read_mask_);
  state_machine.SetBackStencilFunction(back_stencil_compare_function_,
                                       back_reference_value_,
                                       back_stencil_read_mask_);
  state_machine.SetFrontStencilMask(front_stencil_write_mask_);
  state_machine.SetBackStencilMask(back_stencil_write_mask_);
  state_machine.SetFrontStencilOperation(front_stencil_failed_operation_,
                                         front_depth_failed_operation_,
                                         front_test_pass_operation_);
  state_machine.SetBackStencilOperation(back_stencil_failed_operation_,
                                        back_depth_failed_operation_,
                                        back_test_pass_operation_);
}

void RenderPassGL::AfterDraw() {
  // TODO:
  if (curren_framebuffer_ > 0) {
    // Use non-default framebuffer.
    glBindFramebuffer(GL_FRAMEBUFFER, origin_framebuffer_);
  }
}

} // namespace opengl

using RenderPassImplType = ImplType<RenderPass>::type;

static void ApplyRenderPassDescriptor(const RenderPassDescriptor& descriptor,
                                      const std::shared_ptr<RenderPassImplType>& render_pass) {
  render_pass->SetRenderPassDescriptor(descriptor);
}

RenderPass::RenderPass(const RenderPassDescriptor& descriptor)
    : render_pass_(std::make_shared<InternalRenderPass>()) {
  ApplyRenderPassDescriptor(descriptor, render_pass_);
}

RenderPass::~RenderPass() = default;

void RenderPass::SetRenderPiple(const std::shared_ptr<RenderPipeline>& render_pipeline) {
  // TODO:
}

void RenderPass::SetVertexBuffer(const std::shared_ptr<Buffer>& buffer) {
  REZERO_DCHECK(!is_end_) << "RenderPass is end.";
  render_pass_->SetVertexBuffer(buffer);
}

void RenderPass::SetIndexBuffer(const std::shared_ptr<Buffer>& buffer) {
  REZERO_DCHECK(!is_end_) << "RenderPass is end.";
  render_pass_->SetIndexBuffer(buffer);
}

void RenderPass::SetDepthStencilState(
    const std::shared_ptr<DepthStencilState>& depth_stencil_state) {
  REZERO_DCHECK(!is_end_) << "RenderPass is end.";
  REZERO_DCHECK(depth_stencil_state != nullptr);

  render_pass_->SetDepthStencil(depth_stencil_state->GetDescripotr());
}

void RenderPass::SetStencilReferenceValue(unsigned int value) {
  REZERO_DCHECK(!is_end_) << "RenderPass is end.";

  render_pass_->SetReferenceValue(value);
}

void RenderPass::SetStencilReferenceValue(unsigned int front_value,
                                          unsigned int back_value) {
  REZERO_DCHECK(!is_end_) << "RenderPass is end.";

  render_pass_->SetReferenceValue(front_value, back_value);
}

void RenderPass::SetViewport(int x, int y, unsigned int width, unsigned int height) {
  REZERO_DCHECK(!is_end_) << "RenderPass is end.";

  render_pass_->SetViewport(x, y, width, height);
}

void RenderPass::SetScissor(int x, int y, unsigned int width, unsigned int height) {
  REZERO_DCHECK(!is_end_) << "RenderPass is end.";

  render_pass_->SetScissor(x, y, width, height);
}

void RenderPass::SetCullMode(CullMode mode) {
  REZERO_DCHECK(!is_end_) << "RenderPass is end.";

  render_pass_->SetCullMode(mode);
}

void RenderPass::SetWinding(WindingMode mode) {
  REZERO_DCHECK(!is_end_) << "RenderPass is end.";

  render_pass_->SetWindingMode(mode);
}

void RenderPass::DrawArrays(PrimitiveType primitive_type, std::size_t start, std::size_t count) {
  REZERO_DCHECK(!is_end_) << "RenderPass is end.";

  render_pass_->DrawArrays(primitive_type, start, count);
}

void RenderPass::DrawElements(PrimitiveType primitive_type,
                              IndexFormat index_format,
                              std::size_t offset,
                              std::size_t count) {
  REZERO_DCHECK(!is_end_) << "RenderPass is end.";

  render_pass_->DrawElements(primitive_type,
                             index_format,
                             offset,
                             count);
}

void RenderPass::EndRenderPass() {
  is_end_ = true;
  render_pass_->EndRenderPass();
}

} // namespace gpu
} // namespace rezero
