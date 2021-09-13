// Created by Dong Zhong on 2021/09/13.

#include "rezero/base/android/jni_weak_ref.h"

#include "rezero/base/android/jni_util.h"
#include "rezero/base/logging.h"

namespace rezero {
namespace jni {

JavaObjectWeakGlobalRef::JavaObjectWeakGlobalRef() : obj_(NULL) {}

JavaObjectWeakGlobalRef::JavaObjectWeakGlobalRef(const JavaObjectWeakGlobalRef& orig)
    : obj_(NULL) {
  Assign(orig);
}

JavaObjectWeakGlobalRef::JavaObjectWeakGlobalRef(JNIEnv* env, jobject obj)
    : obj_(env->NewWeakGlobalRef(obj)) {
  REZERO_DCHECK(obj_);
}

JavaObjectWeakGlobalRef::~JavaObjectWeakGlobalRef() {
  Reset();
}

void JavaObjectWeakGlobalRef::operator=(const JavaObjectWeakGlobalRef& rhs) {
  Assign(rhs);
}

ScopedJavaLocalRef<jobject> JavaObjectWeakGlobalRef::Get(JNIEnv* env) const {
  return GetRealObject(env, obj_);
}

void JavaObjectWeakGlobalRef::Reset() {
  if (obj_) {
    AttachCurrentThread()->DeleteWeakGlobalRef(obj_);
    obj_ = NULL;
  }
}

void JavaObjectWeakGlobalRef::Assign(const JavaObjectWeakGlobalRef& other) {
  if (&other == this)
    return;

  JNIEnv* env = AttachCurrentThread();
  if (obj_)
    env->DeleteWeakGlobalRef(obj_);

  obj_ = other.obj_ ? env->NewWeakGlobalRef(other.obj_) : NULL;
}

ScopedJavaLocalRef<jobject> GetRealObject(JNIEnv* env, jweak obj) {
  jobject real = NULL;
  if (obj) {
    real = env->NewLocalRef(obj);
    if (!real) {
      REZERO_LOG(ERROR) << "The real object has been deleted!";
    }
  }
  return ScopedJavaLocalRef<jobject>(env, real);
}

} // namespace jni
} // namespace rezero