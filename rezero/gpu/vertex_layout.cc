// Created by Dong Zhong on 2021/11/02.

#include "rezero/gpu/vertex_layout.h"

namespace rezero {
namespace gpu {

VertexLayout::VertexLayout() = default;

VertexLayout::~VertexLayout() = default;

void VertexLayout::SetAttribute(const std::string& name,
                                VertexFormat format,
                                bool need_normalize,
                                std::size_t offset,
                                int index) {
  if (index == -1) {
    return;
  }

  attributes_[name] = { name,
                        format,
                        need_normalize,
                        offset,
                        index };
}

void VertexLayout::SetVertexStride(std::size_t stride) {
  stride_ = stride;
}

} // namespace gpu
} // namespace rezero
