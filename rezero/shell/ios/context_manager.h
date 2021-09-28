// Created by Dong Zhong on 2021/09/26.

#ifndef REZERO_SHELL_IOS_CONTEXT_MANAGER_H_
#define REZERO_SHELL_IOS_CONTEXT_MANAGER_H_

#include <memory>

#include "rezero/base/ios/scoped_nsobject.h"
#include "rezero/base/macros.h"
#include "rezero/shell/ios/rendering_api_selection.h"

@class CALayer;

namespace rezero {
namespace shell {

class ContextManager {
 public:
  static std::unique_ptr<ContextManager> Create(const scoped_nsobject<CALayer>& layer);

  ContextManager(RenderingApi rendering_api);
  virtual ~ContextManager();

  virtual bool Initialize() = 0;
  virtual bool Release() = 0;

  virtual bool CreateRenderTarget() = 0;
  virtual bool TeardownRenderTarget() = 0;
  virtual bool IsRenderTargetValid() const = 0;

  virtual bool MakeCurrent() = 0;

  virtual bool Present() = 0;

  virtual std::pair<int, int> GetDrawableSize() = 0;
  virtual bool UpdateStorageSizeIfNecessary() = 0;

 private:
  const RenderingApi rendering_api_;

  REZERO_DISALLOW_COPY_AND_ASSIGN(ContextManager);
};

} // namespace shell
} // namespace rezero

#endif // REZERO_SHELL_IOS_CONTEXT_MANAGER_H_
