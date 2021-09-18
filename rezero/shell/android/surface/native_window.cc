// Created by Dong Zhong on 2021/09/17.

#include "rezero/shell/android/surface/native_window.h"

namespace rezero {
namespace shell {

NativeWindow::NativeWindow(ANativeWindow* window) : window_(window) {}

NativeWindow::~NativeWindow() {
  if (window_ != nullptr) {
    ANativeWindow_release(window_);
  }
}

bool NativeWindow::IsValid() const {
  return window_ != nullptr;
}

ANativeWindow* NativeWindow::GetWindow() const {
  return window_;
}

} // namespace shell
} // namespace rezero
