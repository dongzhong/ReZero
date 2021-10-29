// Created by Dong Zhong on 2021/10/28.

#ifndef REZERO_GPU_RENDER_PASS_DESCRIPTOR_H_
#define REZERO_GPU_RENDER_PASS_DESCRIPTOR_H_

namespace rezero {
namespace gpu {

struct RenderPassDescriptor {
  RenderPassDescriptor& operator=(const RenderPassDescriptor& other);
  bool operator==(const RenderPassDescriptor& other) const;
};

} // namespace gpu
} // namespace rezero

#endif // REZERO_GPU_RENDER_PASS_DESCRIPTOR_H_
