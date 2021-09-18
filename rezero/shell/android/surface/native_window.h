// Created by Dong Zhong on 2021/09/17.

#ifndef REZERO_SHELL_ANDROID_SURFACE_NATIVE_WINDOW_H_
#define REZERO_SHELL_ANDROID_SURFACE_NATIVE_WINDOW_H_

#include <android/native_window.h>

namespace rezero {
namespace shell {

class NativeWindow {
 public:
  NativeWindow(ANativeWindow* window);
  ~NativeWindow();

  bool IsValid() const;

  ANativeWindow* GetWindow() const;

 private:
  ANativeWindow* window_;
};

} // namespace shell
} // namespace rezero

#endif // REZERO_SHELL_ANDROID_SURFACE_NATIVE_WINDOW_H_
