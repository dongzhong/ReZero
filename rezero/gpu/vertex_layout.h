// Created by Dong Zhong on 2021/11/02.

#ifndef REZERO_GPU_VERTEX_LAYOUT_H_
#define REZERO_GPU_VERTEX_LAYOUT_H_

#include <string>
#include <unordered_map>

#include "rezero/base/macros.h"
#include "rezero/gpu/types.h"

namespace rezero {
namespace gpu {

class VertexLayout {
 public:
  struct Attribute {
    Attribute() = default;

    Attribute(const std::string& name_,
              VertexFormat format_,
              bool need_normalize_,
              std::size_t offset_,
              int index_)
        : name(name_),
          format(format_),
          need_normalize(need_normalize_),
          offset(offset_),
          index(index_) {}

    std::string name;
    VertexFormat format = VertexFormat::kFloat3;
    bool need_normalize = false;
    std::size_t offset = 0;
    int index = 0;
  };

  VertexLayout();
  ~VertexLayout();

  void SetAttribute(const std::string& name,
                    VertexFormat format,
                    bool need_normalize,
                    std::size_t offset,
                    int index);

  void SetVertexStride(std::size_t stride);

  std::size_t GetVertexStride() const { return stride_; }

  std::unordered_map<std::string, Attribute> GetAttributes() const { return attributes_; }

 private:
  std::size_t stride_ = 0;
  std::unordered_map<std::string, Attribute> attributes_;

  REZERO_DISALLOW_COPY_AND_ASSIGN(VertexLayout);
};

} // namespace gpu
} // namespace rezero

#endif // REZERO_GPU_VERTEX_LAYOUT_H_
