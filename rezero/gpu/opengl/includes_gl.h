// Created by Dong Zhong on 2021/11/15.

#ifndef REZERO_GPU_OPENGL_INCLUDES_GL_H_
#define REZERO_GPU_OPENGL_INCLUDES_GL_H_

#include "rezero/base/build_config.h"

#if defined(REZERO_PLATFORM_ANDROID)
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#elif defined(REZERO_PLATFORM_IOS)
#include <OpenGLES/ES3/gl.h>
#include <OpenGLES/ES3/glext.h>
#endif // defined(REZERO_PLATFORM_ANDROID)

#endif // REZERO_GPU_OPENGL_INCLUDES_GL_H_
