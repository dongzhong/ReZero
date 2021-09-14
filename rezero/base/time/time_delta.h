// Created by Dong Zhong on 2021/09/13.

#ifndef REZERO_BASE_TIME_TIME_DELTA_H_
#define REZERO_BASE_TIME_TIME_DELTA_H_

#include <cstdint>
#include <limits>

#include <time.h>

namespace rezero {

class TimeDelta {
 public:
  constexpr TimeDelta() = default;

  static constexpr TimeDelta Zero() { return TimeDelta(); }

  static constexpr TimeDelta Min() {
    return TimeDelta(std::numeric_limits<int64_t>::min());
  }

  static constexpr TimeDelta Max() {
    return TimeDelta(std::numeric_limits<int64_t>::max());
  }

  static constexpr TimeDelta FromNanoseconds(int64_t nanos) {
    return TimeDelta(nanos);
  }

  static constexpr TimeDelta FromMicroseconds(int64_t micros) {
    return FromNanoseconds(micros * 1000);
  }

  static constexpr TimeDelta FromMilliseconds(int64_t millis) {
    return FromMicroseconds(millis * 1000);
  }

  static constexpr TimeDelta FromSeconds(int64_t seconds) {
    return FromMilliseconds(seconds * 1000);
  }

  static constexpr TimeDelta FromSecondsF(double seconds) {
    return FromNanoseconds(seconds * (1000.0 * 1000.0 * 1000.0));
  }

  static constexpr TimeDelta FromMillisecondsF(double millis) {
    return FromNanoseconds(millis * (1000.0 * 1000.0));
  }

  constexpr int64_t ToNanoseconds() const { return delta_; }
  constexpr int64_t ToMicronseconds() const { return ToNanoseconds() / 1000; }
  constexpr int64_t ToMilliseconds() const { return ToMicronseconds() / 1000; }
  constexpr int64_t ToSeconds() const  { return ToMilliseconds() / 1000; }

  constexpr double ToNanosecondsF() const { return delta_; }
  constexpr double ToMicrosecondsF() const { return delta_ / 1000.0; }
  constexpr double ToMillisecondsF() const {
    return delta_ / (1000.0 * 1000.0);
  }
  constexpr double ToSecondsF() const {
    return delta_ / (1000.0 * 1000.0 * 1000.0);
  }

  constexpr TimeDelta operator-(TimeDelta other) const {
    return FromNanoseconds(delta_ - other.delta_);
  }

  constexpr TimeDelta operator+(TimeDelta other) const {
    return FromNanoseconds(delta_ + other.delta_);
  }

  constexpr TimeDelta operator/(int64_t divisor) const {
    return FromNanoseconds(delta_ / divisor);
  }

  constexpr int64_t operator/(TimeDelta other) const {
    return delta_ / other.delta_;
  }

  constexpr TimeDelta operator*(int64_t multiplier) const {
    return FromNanoseconds(delta_ * multiplier);
  }

  constexpr TimeDelta operator%(TimeDelta other) const {
    return FromNanoseconds(delta_ % other.delta_);
  }

  constexpr bool operator==(TimeDelta other) const { return delta_ == other.delta_; }
  constexpr bool operator!=(TimeDelta other) const { return delta_ != other.delta_; }
  constexpr bool operator>(TimeDelta other) const { return delta_ > other.delta_; }
  constexpr bool operator>=(TimeDelta other) const { return delta_ >= other.delta_; }
  constexpr bool operator<(TimeDelta other) const { return delta_ < other.delta_; }
  constexpr bool operator<=(TimeDelta other) const { return delta_ <= other.delta_; }

  static constexpr TimeDelta FromTimespec(struct timespec ts) {
    return FromSeconds(ts.tv_sec) + FromNanoseconds(ts.tv_nsec);
  }

  struct timespec ToTimespec() const {
    struct timespec ts;
    constexpr int64_t kNanosecondsPerSecond = 1000000000ll;
    ts.tv_sec = static_cast<time_t>(ToSeconds());
    ts.tv_nsec = delta_ % kNanosecondsPerSecond;
    return ts;
  }

 private:
  explicit constexpr TimeDelta(int64_t delta) : delta_(delta) {}

  int64_t delta_ = 0;
};

} // namespace rezero

#endif // REZERO_BASE_TIME_TIME_DELTA_H_