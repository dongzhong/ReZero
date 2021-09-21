// Created by Dong Zhong on 2021/09/16.

#include "rezero/shell/android/platform_view_android.h"

#include <android/native_window_jni.h>

#include "rezero/base/android/jni_util.h"
#include "rezero/base/logging.h"
#include "rezero/base/size.h"
#include "rezero/base/waitable_event.h"
#include "rezero/shell/android/engine_android.h"
#include "rezero/shell/android/vsync_waiter_android.h"

namespace rezero {
namespace shell {

static jni::ScopedJavaGlobalRef<jclass>* g_platform_view_class = nullptr;

jlong PlatformViewAndroid::JNICreate(JNIEnv* env, jobject java_caller, jobject java_engine) {
  auto* engine = EngineAndroid::GetFromJavaObj(env, java_engine);
  auto* ptr = new std::shared_ptr<PlatformViewAndroid>(
      std::make_shared<PlatformViewAndroid>((*engine)->GetTaskRunners(),
                                            (*engine)->GetJavaContext()));
  (*engine)->SetPlatformView((*ptr));
  return reinterpret_cast<jlong>(ptr);
}

void PlatformViewAndroid::JNIDestroy(JNIEnv* env, jobject java_caller, jlong native_ptr) {
  if (auto* ptr = reinterpret_cast<std::shared_ptr<PlatformViewAndroid>*>(native_ptr)) {
    delete ptr;
  }
}

void PlatformViewAndroid::JNISurfaceCreate(JNIEnv* env,
                                           jobject java_caller,
                                           jlong native_ptr,
                                           jobject java_surface) {
  if (auto* ptr = reinterpret_cast<std::shared_ptr<PlatformViewAndroid>*>(native_ptr)) {
    (*ptr)->SurfaceCreate(env, java_surface);
  }
}

void PlatformViewAndroid::JNISurfaceDestroy(JNIEnv* env, jobject java_caller, jlong native_ptr) {
  if (auto* ptr = reinterpret_cast<std::shared_ptr<PlatformViewAndroid>*>(native_ptr)) {
    (*ptr)->SurfaceDestroy();
  }
}

void PlatformViewAndroid::JNISurfaceChanged(JNIEnv* env, jobject java_caller, jlong native_ptr) {
  if (auto* ptr = reinterpret_cast<std::shared_ptr<PlatformViewAndroid>*>(native_ptr)) {
    (*ptr)->SurfaceChanged();
  }
}

const JNINativeMethod PlatformViewAndroid::kJNIMethods[] = {
    {
        .name = "nativeCreate",
        .signature = "(Lpers/dongzhong/rezero/ReZeroView;)J",
        .fnPtr = reinterpret_cast<void*>(&PlatformViewAndroid::JNICreate),
    },
    {
        .name = "nativeDestroy",
        .signature = "(J)V",
        .fnPtr = reinterpret_cast<void*>(&PlatformViewAndroid::JNIDestroy),
    },
    {
        .name = "nativeSurfaceCreate",
        .signature = "(JLandroid/view/Surface;)V",
        .fnPtr = reinterpret_cast<void*>(&PlatformViewAndroid::JNISurfaceCreate),
    },
    {
        .name = "nativeSurfaceDestroy",
        .signature = "(J)V",
        .fnPtr = reinterpret_cast<void*>(&PlatformViewAndroid::JNISurfaceDestroy),
    },
    {
        .name = "nativeSurfaceChanged",
        .signature = "(J)V",
        .fnPtr = reinterpret_cast<void*>(&PlatformViewAndroid::JNISurfaceChanged),
    },
};

void PlatformViewAndroid::Register(JNIEnv* env) {
  auto clazz = jni::ScopedJavaLocalRef<jclass>(
      env, env->FindClass("pers/dongzhong/rezero/PlatformView"));
  REZERO_DCHECK(!clazz.is_null());

  g_platform_view_class = new jni::ScopedJavaGlobalRef<jclass>(clazz);
  REZERO_DCHECK(!g_platform_view_class->is_null());

  auto res = env->RegisterNatives(clazz.obj(), kJNIMethods, size(kJNIMethods));
  REZERO_DCHECK(res == 0);
}

PlatformViewAndroid::PlatformViewAndroid(
    const std::shared_ptr<TaskRunners>& task_runners,
    const jni::ScopedJavaGlobalRef<jobject>& java_context)
    : PlatformView(task_runners) {
  CreateVsyncWaiter(java_context);
}

PlatformViewAndroid::~PlatformViewAndroid() = default;

void PlatformViewAndroid::CreateVsyncWaiter(
    const jni::ScopedJavaGlobalRef<jobject>& java_context) {
  vsync_waiter_ = VsyncWaiterAndroid::Create(task_runners_,
                                             java_context);
  REZERO_DCHECK(vsync_waiter_);
}

void PlatformViewAndroid::SurfaceCreate(JNIEnv* env, jobject java_surface) {
  ANativeWindow* native_window = ANativeWindow_fromSurface(env, java_surface);

  AutoResetWaitableEvent latch;
  task_runners_->GetMainTaskRunner()->PostTask([this, native_window, &latch]() {
    native_window_ = std::make_shared<NativeWindow>(native_window);

    // TODO: Start to render

    latch.Signal();
  });
  latch.Wait();
}

void PlatformViewAndroid::SurfaceDestroy() {
  AutoResetWaitableEvent latch;
  task_runners_->GetMainTaskRunner()->PostTask([this, &latch]() {
    // TODO: Pause rendering

    native_window_ = nullptr;

    latch.Signal();
  });
  latch.Wait();
}

void PlatformViewAndroid::SurfaceChanged() {
  // TODO:
}

} // namespace shell
} // namespace rezero