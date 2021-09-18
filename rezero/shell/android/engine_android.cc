// Created by Dong Zhong on 2021/09/13.

#include "rezero/shell/android/engine_android.h"

#include "rezero/base/android/jni_util.h"
#include "rezero/base/logging.h"
#include "rezero/base/size.h"
#include "rezero/version.h"

namespace rezero {
namespace shell {

static jni::ScopedJavaGlobalRef<jclass>* g_rezero_view_class = nullptr;
static jfieldID g_native_ptr_field = nullptr;

jobject EngineAndroid::JNIGetVersion(JNIEnv* env, jclass java_caller) {
  return env->NewStringUTF(kVersion);
}

jlong EngineAndroid::JNICreate(JNIEnv* env,
                               jobject java_caller,
                               jobject java_context) {
  auto* ptr = new std::unique_ptr<EngineAndroid>(
      EngineAndroid::Create(jni::ScopedJavaLocalRef<jobject>(env, java_context)));
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

  g_native_ptr_field = env->GetFieldID(clazz.obj(), "nativePtr", "J");
  REZERO_DCHECK(g_native_ptr_field);
}

std::unique_ptr<EngineAndroid>* EngineAndroid::GetFromJavaObj(
    JNIEnv* env, jobject java_obj) {
  jlong ptr = env->GetLongField(java_obj, g_native_ptr_field);
  REZERO_DCHECK(ptr);

  return reinterpret_cast<std::unique_ptr<EngineAndroid>*>(ptr);
}

std::unique_ptr<EngineAndroid> EngineAndroid::Create(
    const jni::JavaRef<jobject>& java_context) {
  return std::make_unique<EngineAndroid>(java_context);
}

EngineAndroid::EngineAndroid(const jni::JavaRef<jobject>& java_context)
    : java_context_(java_context) {
  REZERO_DCHECK(!java_context_.is_null());
}

EngineAndroid::~EngineAndroid() = default;

} // namespace shell
} // namespace rezero