// Created by Dong Zhong on 2021/09/13.

#ifndef REZERO_BASE_BUILD_CONFIG_H_
#define REZERO_BASE_BUILD_CONFIG_H_

#if defined(ANDROID)

#define REZERO_PLATFORM_ANDROID

#elif defined(__APPLE__)

#include <TargetConditionals.h>

#if defined(TARGET_OS_IPHONE) && TARGET_OS_IPHONE

#define REZERO_PLATFORM_IOS

#endif // defined(TARGET_OS_IPHONE) && TARGET_OS_IPHONE

#else

#error "Cannot recognize the target platform."

#endif // defined(ANDROID)

#endif // REZERO_BASE_BUILD_CONFIG_H_
