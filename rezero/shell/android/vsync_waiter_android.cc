// Created by Dong Zhong on 2021/09/18.

#include "rezero/shell/android/vsync_waiter_android.h"

#include <memory>

#include "rezero/base/logging.h"
#include "rezero/base/size.h"

namespace rezero {
namespace shell {

static jni::ScopedJavaGlobalRef<jclass>* g_vsync_waiter_class = nullptr;
static jmethodID g_create_method = nullptr;
static jmethodID g_await_vsync_method = nullptr;
static jmethodID g_release_method = nullptr;

void VsyncWaiterAndroid::JNIOnVsync(JNIEnv* env,
                                    jclass java_caller,
                                    jlong frame_start_time,
                                    jlong frame_end_time,
                                    jlong weak_native_ptr) {
  TimePoint start_time_point = TimePoint::FromEpochDelta(
      TimeDelta::FromNanoseconds(frame_start_time));
  TimePoint end_time_point = TimePoint::FromEpochDelta(
      TimeDelta::FromNanoseconds(frame_end_time));
  auto* weak_ptr = reinterpret_cast<std::weak_ptr<VsyncWaiterAndroid>*>(weak_native_ptr);
  if (weak_ptr) {
    if (auto shared_ptr = weak_ptr->lock()) {
      shared_ptr->FireCallback(start_time_point, end_time_point);
    }
  }
}

void VsyncWaiterAndroid::JNIRelease(JNIEnv* env, jobject java_caller, jlong weak_native_ptr) {
  auto* weak_ptr = reinterpret_cast<std::weak_ptr<VsyncWaiterAndroid>*>(weak_native_ptr);
  if (weak_ptr) {
    delete weak_ptr;
  }
}

const JNINativeMethod VsyncWaiterAndroid::kJNIMethods[] = {
    {
        .name = "nativeOnVsync",
        .signature = "(JJJ)V",
        .fnPtr = reinterpret_cast<void*>(&VsyncWaiterAndroid::JNIOnVsync),
    },
    {
        .name = "nativeRelease",
        .signature = "(J)V",
        .fnPtr = reinterpret_cast<void*>(&VsyncWaiterAndroid::JNIRelease),
    },
};

void VsyncWaiterAndroid::Register(JNIEnv* env) {
  jni::ScopedJavaLocalRef<jclass> clazz;

  clazz.Reset(jni::ScopedJavaLocalRef<jclass>(
      env, env->FindClass("pers/dongzhong/rezero/VsyncWaiter")));
  REZERO_DCHECK(!clazz.is_null());

  g_vsync_waiter_class = new jni::ScopedJavaGlobalRef<jclass>(clazz);
  REZERO_DCHECK(!g_vsync_waiter_class->is_null());

  auto res = env->RegisterNatives(clazz.obj(), kJNIMethods, size(kJNIMethods));
  REZERO_DCHECK(res == 0);

  g_create_method = env->GetStaticMethodID(
      clazz.obj(), "create",
      "(Landroid/content/Context;J)Lpers/dongzhong/rezero/VsyncWaiter;");
  REZERO_DCHECK(g_create_method);

  g_await_vsync_method = env->GetMethodID(clazz.obj(), "awaitVsync", "()V");
  REZERO_DCHECK(g_await_vsync_method);

  g_release_method = env->GetMethodID(clazz.obj(), "nativeRelease", "(J)V");
  REZERO_DCHECK(g_release_method);
}

std::shared_ptr<VsyncWaiterAndroid> VsyncWaiterAndroid::Create(
    const std::shared_ptr<TaskRunners>& task_runners,
    const jni::ScopedJavaGlobalRef<jobject>& java_context) {
  auto* env = jni::AttachCurrentThread();
  auto vsync_waiter = std::make_shared<VsyncWaiterAndroid>(task_runners);
  auto java_vsync_waiter = jni::ScopedJavaGlobalRef<jobject>(
      env, env->CallStaticObjectMethod(g_vsync_waiter_class->obj(),
                                       g_create_method,
                                       java_context.obj(),
                                       reinterpret_cast<jlong>(new std::weak_ptr<VsyncWaiterAndroid>(vsync_waiter))));
  REZERO_CHECK(!jni::ClearException(env));
  vsync_waiter->SetJavaVsyncWaiter(java_vsync_waiter);
  return vsync_waiter;
}

VsyncWaiterAndroid::VsyncWaiterAndroid(const std::shared_ptr<TaskRunners>& task_runners)
    : VsyncWaiter(task_runners) {}

VsyncWaiterAndroid::~VsyncWaiterAndroid() {
  auto* env = jni::AttachCurrentThread();
  env->CallVoidMethod(java_vsync_waiter_.obj(), g_release_method);
  REZERO_CHECK(!jni::ClearException(env));
}

void VsyncWaiterAndroid::AwaitVsync() {
  task_runners_->GetPlatformTaskRunner()->PostTask([weak_this = weak_from_this()]() {
    if (auto shared_this = weak_this.lock()) {
      JNIEnv* env = jni::AttachCurrentThread();
      env->CallVoidMethod(shared_this->java_vsync_waiter_.obj(),
                          g_await_vsync_method);
      REZERO_CHECK(!jni::ClearException(env));
    }
  });
}

void VsyncWaiterAndroid::SetJavaVsyncWaiter(const jni::JavaRef<jobject>& java_vsync_waiter) {
  java_vsync_waiter_.Reset(java_vsync_waiter);
  REZERO_DCHECK(!java_vsync_waiter_.is_null());
}

} // namespace shell
} // namespace rezero