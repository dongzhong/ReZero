// Created by Dong Zhong on 2021/09/16.

#ifndef REZERO_SHELL_ANDROID_PLATFORM_VIEW_ANDROID_H_
#define REZERO_SHELL_ANDROID_PLATFORM_VIEW_ANDROID_H_

#include "rezero/base/android/jni_util.h"
#include "rezero/shell/platform_view.h"
#include "rezero/shell/android/surface/native_window.h"

namespace rezero {
namespace shell {

class PlatformViewAndroid final : public PlatformView {
 public:
  static void Register(JNIEnv* env);

  PlatformViewAndroid(const std::shared_ptr<TaskRunner>& main_task_runner);
  ~PlatformViewAndroid() override;

 private:
  static jlong JNICreate(JNIEnv* env, jobject java_caller, jobject java_engine);

  static void JNIDestroy(JNIEnv* env, jobject java_caller, jlong native_ptr);

  static void JNISurfaceCreate(JNIEnv* env, jobject java_caller, jlong native_ptr, jobject java_surface);

  static void JNISurfaceDestroy(JNIEnv* env, jobject java_caller, jlong native_ptr);

  static void JNISurfaceChanged(JNIEnv* env, jobject java_caller, jlong native_ptr);

  static const JNINativeMethod kJNIMethods[];

  void SurfaceCreate(JNIEnv* env, jobject java_surface);

  void SurfaceDestroy();

  void SurfaceChanged();

  std::shared_ptr<NativeWindow> native_window_;

  REZERO_DISALLOW_COPY_AND_ASSIGN(PlatformViewAndroid);
};

} // namespace shell
} // namespace rezero

#endif // REZERO_SHELL_ANDROID_PLATFORM_VIEW_ANDROID_H_