// Created by Dong Zhong on 2021/09/18.

#ifndef REZERO_SHELL_ANDROID_VSYNC_WAITER_ANDROID_H_
#define REZERO_SHELL_ANDROID_VSYNC_WAITER_ANDROID_H_

#include "rezero/base/android/jni_util.h"
#include "rezero/shell/vsync_waiter.h"

namespace rezero {
namespace shell {

class VsyncWaiterAndroid final : public VsyncWaiter,
                                 public std::enable_shared_from_this<VsyncWaiterAndroid> {
 public:
  static void Register(JNIEnv* env);

  static std::shared_ptr<VsyncWaiterAndroid> Create(const std::shared_ptr<TaskRunners>& task_runners,
                                                    const jni::ScopedJavaGlobalRef<jobject>& java_context);

  VsyncWaiterAndroid(const std::shared_ptr<TaskRunners>& task_runners);
  ~VsyncWaiterAndroid() override;

 protected:
  static void JNIOnVsync(JNIEnv* env,
                         jclass java_caller,
                         jlong frame_start_time,
                         jlong frame_end_time,
                         jlong weak_native_ptr);

  static void JNIRelease(JNIEnv* env, jobject java_caller, jlong weak_native_ptr);

  static const JNINativeMethod kJNIMethods[];

  void AwaitVsync() override;

 private:
  void SetJavaVsyncWaiter(const jni::JavaRef<jobject>& java_vsync_waiter);

  jni::ScopedJavaGlobalRef<jobject> java_vsync_waiter_;

  REZERO_DISALLOW_COPY_AND_ASSIGN(VsyncWaiterAndroid);
};

} // namespace shell
} // namespace rezero

#endif // REZERO_SHELL_ANDROID_VSYNC_WAITER_ANDROID_H_