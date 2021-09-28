// Created by Dong Zhong on 2021/09/25.

#include "rezero/shell/android/native_window_android.h"

namespace rezero {
namespace shell {

NativeWindowAndroid::NativeWindowAndroid(ANativeWindow* window) : window_(window) {}

NativeWindowAndroid::~NativeWindowAndroid() {
  if (window_ != nullptr) {
    ANativeWindow_release(window_);
  }
}

bool NativeWindowAndroid::IsValid() const {
  return window_ != nullptr;
}

ANativeWindow* NativeWindowAndroid::GetWindow() const {
  return window_;
}

} // namespace shell
} // namespace rezero
