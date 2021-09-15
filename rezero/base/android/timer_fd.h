// Created by Dong Zhong on 2021/09/15.

#ifndef REZERO_BASE_ANDROID_TIMER_FD_H_
#define REZERO_BASE_ANDROID_TIMER_FD_H_

#include "rezero/base/time/time_point.h"

// clang-format off
#if __has_include(<sys/timerfd.h>) && \
    (!defined(__ANDROID_API__) || __ANDROID_API__ >= 19)
    // sys/timerfd.h is always present in Android NDK due to unified headers,
    // but timerfd functions are only available on API 19 or later.
// clang-format on

#include <sys/timerfd.h>

#define REZERO_TIMERFD_AVAILABLE 1

#else

#define REZERO_TIMERFD_AVAILABLE 0

#include <sys/types.h>
#include <linux/time.h>

#define TFD_TIMER_ABSTIME (1 << 0)
#define TFD_TIMER_CANCEL_ON_SET (1 << 1)

#define TFD_CLOEXEC O_CLOEXEC
#define TFD_NONBLOCK O_NONBLOCK

int timerfd_create(int clockid, int flags);

int timerfd_settime(int ufc,
                    int flags,
                    const struct itimerspec* utmr,
                    struct itimerspec* otmr);

#endif // __has_include(<sys/timerfd.h>)

namespace rezero {

bool TimerRearm(int fd, TimePoint time_point);

bool TimerDrain(int fd);

} // namespace rezero

#endif // REZERO_BASE_ANDROID_TIMER_FD_H_