// Created by Dong Zhong on 2021/09/13.

#ifndef REZERO_SHELL_ANDROID_ENGINE_ANDROID_H_
#define REZERO_SHELL_ANDROID_ENGINE_ANDROID_H_

#include <memory>

#include <jni.h>

#include "rezero/shell/android/platform_view_android.h"
#include "rezero/shell/engine.h"

namespace rezero {
namespace shell {

class EngineAndroid final : public Engine {
 public:
  static void Register(JNIEnv* env);

  static std::unique_ptr<EngineAndroid> Create(const jni::JavaRef<jobject>& java_context);

  EngineAndroid(const jni::JavaRef<jobject>& java_context);
  ~EngineAndroid() override;

  static std::unique_ptr<EngineAndroid>* GetFromJavaObj(JNIEnv* env, jobject java_obj);

 private:
  static jobject JNIGetVersion(JNIEnv* env, jclass java_caller);

  static jlong JNICreate(JNIEnv* env, jobject java_caller, jobject java_context);

  static void JNIRelease(JNIEnv* env, jobject java_caller, jlong native_ptr);

  static const JNINativeMethod kJNIMethods[];

  jni::ScopedJavaLocalRef<jobject> java_context_;

  REZERO_DISALLOW_COPY_AND_ASSIGN(EngineAndroid);
};

} // namespace shell
} // namespace rezero

#endif // REZERO_SHELL_ANDROID_ENGINE_ANDROID_H_