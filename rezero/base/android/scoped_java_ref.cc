// Created by Dong Zhong on 2021/09/13.

#include "rezero/base/android/scoped_java_ref.h"

#include "rezero/base/android/jni_util.h"
#include "rezero/base/logging.h"

namespace rezero {
namespace jni {

static const int kDefaultLocalFrameCapacity = 16;

ScopedJavaLocalFrame::ScopedJavaLocalFrame(JNIEnv* env)
    : env_(env) {
  int failed = env_->PushLocalFrame(kDefaultLocalFrameCapacity);
  REZERO_DCHECK(!failed);
}

ScopedJavaLocalFrame::ScopedJavaLocalFrame(JNIEnv* env, int capacity)
    : env_(env) {
  int failed = env_->PushLocalFrame(capacity);
  REZERO_DCHECK(!failed);
}

ScopedJavaLocalFrame::~ScopedJavaLocalFrame() {
  env_->PopLocalFrame(NULL);
}

JavaRef<jobject>::JavaRef() : obj_(NULL) {}

JavaRef<jobject>::JavaRef(JNIEnv* env, jobject obj)
    : obj_(obj) {
  if (obj_) {
    REZERO_DCHECK(env && env->GetObjectRefType(obj_) == JNILocalRefType);
  }
}

JavaRef<jobject>::~JavaRef() = default;

JNIEnv* JavaRef<jobject>::SetNewLocalRef(JNIEnv* env, jobject obj) {
  if (!env) {
    env = AttachCurrentThread();
  } else {
    REZERO_CHECK(env == AttachCurrentThread());  // Is |env| on correct thread.
  }
  if (obj)
    obj = env->NewLocalRef(obj);
  if (obj_)
    env->DeleteLocalRef(obj_);
  obj_ = obj;
  return env;
}

void JavaRef<jobject>::SetNewGlobalRef(JNIEnv* env, jobject obj) {
  if (!env) {
    env = AttachCurrentThread();
  } else {
    REZERO_CHECK(env == AttachCurrentThread());  // Is |env| on correct thread.
  }
  if (obj)
    obj = env->NewGlobalRef(obj);
  if (obj_)
    env->DeleteGlobalRef(obj_);
  obj_ = obj;
}

void JavaRef<jobject>::ResetLocalRef(JNIEnv* env) {
  if (obj_) {
    REZERO_DCHECK(env == AttachCurrentThread());  // Is |env| on correct thread.
    env->DeleteLocalRef(obj_);
    obj_ = NULL;
  }
}

void JavaRef<jobject>::ResetGlobalRef() {
  if (obj_) {
    AttachCurrentThread()->DeleteGlobalRef(obj_);
    obj_ = NULL;
  }
}

jobject JavaRef<jobject>::ReleaseInternal() {
  jobject obj = obj_;
  obj_ = NULL;
  return obj;
}

} // namespace jni
} // namespace rezero