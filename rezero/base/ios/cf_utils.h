// Created by Dong Zhong on 2021/09/14.

#ifndef REZERO_BASE_IOS_CF_UTILS_H_
#define REZERO_BASE_IOS_CF_UTILS_H_

#import <CoreFoundation/CoreFoundation.h>

namespace rezero {

template <typename CFT>
class CFRef {
 public:
  CFRef() : instance_(nullptr) {}

  CFRef(CFT instance) : instance_(instance) {}

  CFRef(const CFRef& other) : instance_(other.instance_) {
    if (instance_) {
      CFRetain(instance_);
    }
  }

  CFRef(CFRef&& other) : instance_(other.instance_) {
    other.instance_ = nullptr;
  }

  CFRef& operator=(CFRef&& other) {
    Reset(other.Release());
    return *this;
  }

  ~CFRef() {
    if (instance_ != nullptr) {
      CFRelease(instance_);
    }
    instance_ = nullptr;
  }

  void Reset(CFT instance = nullptr) {
    if (instance_ == instance) {
      return;
    }
    if (instance_ != nullptr) {
      CFRelease(instance_);
    }
    instance_ = instance;
  }

  [[nodiscard]] CFT Release() {
    auto instance = instance_;
    instance_ = nullptr;
    return instance;
  }

  operator CFT() const { return instance_; }

  operator bool() const { return instance_ != nullptr; }

 private:
  CFT instance_;

  CFRef& operator=(const CFRef&) = delete;
};

} // namespace rezero

#endif // REZERO_BASE_IOS_CF_UTILS_H_
