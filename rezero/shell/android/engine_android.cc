// Created by Dong Zhong on 2021/09/13.

#include "rezero/shell/android/engine_android.h"

#include "rezero/base/android/jni_util.h"
#include "rezero/base/logging.h"
#include "rezero/base/size.h"
#include "rezero/version.h"

namespace rezero {
namespace shell {

static jni::ScopedJavaGlobalRef<jclass>* g_rezero_view_class = nullptr;

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
  auto clazz = jni::ScopedJavaLocalRef<jclass>(
      env, env->FindClass("pers/dongzhong/rezero/ReZeroView"));
  REZERO_DCHECK(!clazz.is_null());

  g_rezero_view_class = new jni::ScopedJavaGlobalRef<jclass>(clazz);
  REZERO_DCHECK(!g_rezero_view_class->is_null());

  auto res = env->RegisterNatives(clazz.obj(), kJNIMethods, size(kJNIMethods));
  REZERO_DCHECK(res == 0);
}

std::unique_ptr<EngineAndroid> EngineAndroid::Create() {
  return std::make_unique<EngineAndroid>();
}

EngineAndroid::EngineAndroid() = default;

EngineAndroid::~EngineAndroid() = default;

} // namespace shell
} // namespace rezero