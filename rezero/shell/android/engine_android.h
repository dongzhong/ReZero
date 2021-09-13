// Created by Dong Zhong on 2021/09/13.

#ifndef REZERO_SHELL_ANDROID_ENGINE_ANDROID_H_
#define REZERO_SHELL_ANDROID_ENGINE_ANDROID_H_

#include <memory>

#include <jni.h>

#include "rezero/shell/engine.h"

namespace rezero {
namespace shell {

class EngineAndroid final : public Engine {
 public:
  static void Register(JNIEnv* env);

  static std::unique_ptr<EngineAndroid> Create();

  EngineAndroid();
  ~EngineAndroid() override;

 private:
  static jobject JNIGetVersion(JNIEnv* env, jclass java_caller);

  static jlong JNICreate(JNIEnv* env, jobject java_caller, jobject java_context);

  static void JNIRelease(JNIEnv* env, jobject java_caller, jlong native_ptr);

  static const JNINativeMethod kJNIMethods[];

  REZERO_DISALLOW_COPY_AND_ASSIGN(EngineAndroid);
};

} // namespace shell
} // namespace rezero

#endif // REZERO_SHELL_ANDROID_ENGINE_ANDROID_H_