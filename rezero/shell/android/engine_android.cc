// Created by Dong Zhong on 2021/09/13.

#include "rezero/shell/android/engine_android.h"

#include "rezero/base/size.h"
#include "rezero/version.h"

namespace rezero {
namespace shell {

static jclass g_rezero_view_class = nullptr;

jobject EngineAndroid::JNIGetVersion(JNIEnv* env, jclass java_caller) {
  return env->NewStringUTF(kVersion);
}

jlong EngineAndroid::JNICreate(JNIEnv* env, jobject java_caller, jobject java_context) {
  auto* ptr = new std::unique_ptr<EngineAndroid>(
      EngineAndroid::Create());
  return reinterpret_cast<jlong>(ptr);
}

void EngineAndroid::JNIRelease(JNIEnv* env, jobject java_caller, jlong native_ptr) {
  auto* ptr = reinterpret_cast<std::unique_ptr<EngineAndroid>*>(native_ptr);
  if (ptr) {
    delete ptr;
  }
}

const JNINativeMethod EngineAndroid::kJNIMethods[] = {
    {
        .name = "nativeGetVersion",
        .signature = "()Ljava/lang/String;",
        .fnPtr = reinterpret_cast<void*>(&EngineAndroid::JNIGetVersion),
    },
    {
        .name = "nativeCreate",
        .signature = "(Landroid/content/Context;)J",
        .fnPtr = reinterpret_cast<void*>(&EngineAndroid::JNICreate),
    },
    {
        .name = "nativeRelease",
        .signature = "(J)V",
        .fnPtr = reinterpret_cast<void*>(&EngineAndroid::JNIRelease),
    },
};

void EngineAndroid::Register(JNIEnv* env) {
  g_rezero_view_class = env->FindClass("pers/dongzhong/rezero/ReZeroView");

  env->RegisterNatives(g_rezero_view_class, kJNIMethods, size(kJNIMethods));
}

std::unique_ptr<EngineAndroid> EngineAndroid::Create() {
  return std::make_unique<EngineAndroid>();
}

EngineAndroid::EngineAndroid() = default;

EngineAndroid::~EngineAndroid() = default;

} // namespace shell
} // namespace rezero