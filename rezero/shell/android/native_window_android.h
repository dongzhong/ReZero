// Created by Dong Zhong on 2021/09/25.

#ifndef REZERO_SHELL_ANDROID_NATIVE_WINDOW_ANDROID_H_
#define REZERO_SHELL_ANDROID_NATIVE_WINDOW_ANDROID_H_

#include <android/native_window.h>

namespace rezero {
namespace shell {

class NativeWindowAndroid {
 public:
  NativeWindowAndroid(ANativeWindow* window);
  ~NativeWindowAndroid();

  bool IsValid() const;

  ANativeWindow* GetWindow() const;

 private:
  ANativeWindow* window_;
};

} // namespace shell
} // namespace rezero

#endif // REZERO_SHELL_ANDROID_NATIVE_WINDOW_ANDROID_H_
