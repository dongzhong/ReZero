// Created by Dong Zhong on 2021/09/15.

#include "rezero/base/android/timer_fd.h"

#include <sys/types.h>
#include <unistd.h>

#include "rezero/base/eintr_wrapper.h"

#if REZERO_TIMERFD_AVAILABLE == 0

#include <asm/unistd.h>
#include <sys/syscall.h>

int timerfd_create(int clockid, int flags) {
  return syscall(__NR_timer_create, clockid, flags);
}

int timerfd_settime(int ufc,
                    int flags,
                    const struct itimerspec* utmr,
                    struct itimerspec* otmr) {
  return syscall(__NR_timer_settime, ufc, flags, utmr, otmr);
}

#endif // RREZERO_TIMERFD_AVAILABLE == 0

namespace rezero {

#ifndef NSEC_PER_SEC
#define NSEC_PER_SEC 1000000000
#endif

bool TimerRearm(int fd, TimePoint time_point) {
  uint64_t nano_secs = time_point.ToEpochDelta().ToNanoseconds();

  if (nano_secs < 1) {
    nano_secs = 1;
  }

  struct itimerspec spec = {};
  spec.it_value.tv_sec = (time_t)(nano_secs / NSEC_PER_SEC);
  spec.it_value.tv_nsec = nano_secs % NSEC_PER_SEC;
  spec.it_interval = spec.it_value;

  int result = ::timerfd_settime(fd, TFD_TIMER_ABSTIME, &spec, nullptr);
  return result == 0;
}

bool TimerDrain(int fd) {
  uint64_t fire_count = 0;
  ssize_t size = REZERO_HANDLE_EINTR(::read(fd, &fire_count, sizeof(uint64_t)));
  if (size != sizeof(uint64_t)) {
    return false;
  }
  return fire_count > 0;
}

} // namespace rezero