// Created by Dong Zhong on 2021/09/16.

#ifndef REZERO_SHELL_ANDROID_PLATFORM_VIEW_ANDROID_H_
#define REZERO_SHELL_ANDROID_PLATFORM_VIEW_ANDROID_H_

#include "rezero/base/android/scoped_java_ref.h"
#include "rezero/shell/android/context_manager.h"
#include "rezero/shell/android/native_window_android.h"
#include "rezero/shell/platform_view.h"

namespace rezero {
namespace shell {

class PlatformViewAndroid final : public PlatformView {
 public:
  static void Register(JNIEnv* env);

  PlatformViewAndroid(const std::shared_ptr<TaskRunners>& task_runners,
                      const jni::ScopedJavaGlobalRef<jobject>& java_context);
  ~PlatformViewAndroid() override;

 private:
  static jlong JNICreate(JNIEnv* env, jobject java_caller, jobject java_engine);

  static void JNIDestroy(JNIEnv* env, jobject java_caller, jlong native_ptr);

  static void JNISurfaceCreate(JNIEnv* env, jobject java_caller, jlong native_ptr, jobject java_surface);

  static void JNISurfaceDestroy(JNIEnv* env, jobject java_caller, jlong native_ptr);

  static void JNISurfaceSizeChanged(JNIEnv* env, jobject java_caller, jlong native_ptr, jint width, jint height);

  static void JNISetVisibilityChanged(JNIEnv* env, jobject java_caller, jlong native_ptr, jboolean visibility);

  static const JNINativeMethod kJNIMethods[];

  void CreateVsyncWaiter(const jni::ScopedJavaGlobalRef<jobject>& java_context);

  void SurfaceCreate(JNIEnv* env, jobject java_surface);

  void SurfaceDestroy();

  void SurfaceSizeChanged(int width, int height);

  void OnVisibilityChanged(bool visibility);

  bool Present() override;

  std::unique_ptr<ContextManager> context_manager_;
  bool is_visible_ = false;

  REZERO_DISALLOW_COPY_AND_ASSIGN(PlatformViewAndroid);
};

} // namespace shell
} // namespace rezero

#endif // REZERO_SHELL_ANDROID_PLATFORM_VIEW_ANDROID_H_