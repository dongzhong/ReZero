// Created by Dong Zhong on 2021/10/28.

#ifndef REZERO_GPU_DEFINES_H_
#define REZERO_GPU_DEFINES_H_

#include "rezero/base/macros.h"

#if defined(REZERO_GPU_OPENGL)

#define REZERO_GPU_BACKEND_PREFIX rezero/gpu/opengl/traits/trait_

#define REZERO_GPU_BACKEND(File) \
  REZERO_MACRO_TO_STRING(REZERO_MACRO_JOIN(REZERO_GPU_BACKEND_PREFIX, File))

#else

#error "Unknown GPU backend."

#endif // defined(REZERO_GPU_BACKEND_OPENGL)

#endif // REZERO_GPU_DEFINES_H_
