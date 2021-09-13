// Created by Dong Zhong on 2021/09/13.

#ifndef REZERO_BASE_ANDROID_JNI_UTIL_H_
#define REZERO_BASE_ANDROID_JNI_UTIL_H_

#include <jni.h>
#include <vector>

#include "rezero/base/android/scoped_java_ref.h"

namespace rezero {
namespace jni {

void InitJavaVM(JavaVM* vm);

JNIEnv* AttachCurrentThread();

void DetachFromVM();

std::string JavaStringToString(JNIEnv* env, jstring string);

ScopedJavaLocalRef<jstring> StringToJavaString(JNIEnv* env,
                                               const std::string& str);

std::vector<std::string> StringArrayToVector(JNIEnv* env, jobjectArray jargs);

ScopedJavaLocalRef<jobjectArray> VectorToStringArray(
    JNIEnv* env,
    const std::vector<std::string>& vector);

bool HasException(JNIEnv* env);

bool ClearException(JNIEnv* env);

std::string GetJavaExceptionInfo(JNIEnv* env, jthrowable java_throwable);

} // namespace jni
} // namespace rezero

#endif // REZERO_BASE_ANDROID_JNI_UTIL_H_