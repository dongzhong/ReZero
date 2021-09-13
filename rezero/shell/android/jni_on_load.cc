// Created by Dong Zhong on 2021/09/13.

#include <jni.h>

#include "rezero/base/logging.h"
#include "rezero/shell/android/engine_android.h"

extern "C" JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved) {
  JNIEnv* env;
  auto ret = vm->GetEnv((void**)&env, JNI_VERSION_1_4);
  REZERO_DCHECK(ret == JNI_OK);

  rezero::shell::EngineAndroid::Register(env);

  return JNI_VERSION_1_4;
}