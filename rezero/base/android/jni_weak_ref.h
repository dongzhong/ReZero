// Created by Dong Zhong on 2021/09/13.

#ifndef REZERO_BASE_ANDROID_JNI_WEAK_REF_H_
#define REZERO_BASE_ANDROID_JNI_WEAK_REF_H_

#include <jni.h>

#include "rezero/base/android/scoped_java_ref.h"

namespace rezero {
namespace jni {

class JavaObjectWeakGlobalRef {
 public:
  JavaObjectWeakGlobalRef();

  JavaObjectWeakGlobalRef(const JavaObjectWeakGlobalRef& orig);

  JavaObjectWeakGlobalRef(JNIEnv* env, jobject obj);

  virtual ~JavaObjectWeakGlobalRef();

  void operator=(const JavaObjectWeakGlobalRef& rhs);

  ScopedJavaLocalRef<jobject> Get(JNIEnv* env) const;

  bool IsEmpty() const { return obj_ == NULL; }

  void Reset();

 private:
  void Assign(const JavaObjectWeakGlobalRef& other);

  jweak obj_;
};

ScopedJavaLocalRef<jobject> GetRealObject(JNIEnv* env, jweak obj);

} // namespace jni
} // namespace rezero

#endif // REZERO_BASE_ANDROID_JNI_WEAK_REF_H_