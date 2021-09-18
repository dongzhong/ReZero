// Created by Dong Zhong on 2021/09/13.

#ifndef REZERO_BASE_IOS_SCOPED_NSOBJECT_H_
#define REZERO_BASE_IOS_SCOPED_NSOBJECT_H_

#import <Foundation/NSObject.h>

#include "rezero/base/macros.h"

@class NSAutoreleasePool;

namespace rezero {

template <typename NST>
class scoped_nsprotocol {
 public:
  explicit scoped_nsprotocol(NST object = nil) : object_(object) {}

  scoped_nsprotocol(const scoped_nsprotocol<NST>& that) : object_([that.object_ retain]) {}

  template <typename NSU>
  scoped_nsprotocol(const scoped_nsprotocol<NSU>& that) : object_([that.get() retain]) {}

  ~scoped_nsprotocol() { [object_ release]; }

  scoped_nsprotocol& operator=(const scoped_nsprotocol<NST>& that) {
    reset([that.get() retain]);
    return *this;
  }

  void reset(NST object = nil) {
    [object_ release];
    object_ = object;
  }

  bool operator==(NST that) const { return object_ == that; }
  bool operator!=(NST that) const { return object_ != that; }

  operator NST() const { return object_; }

  NST get() const { return object_; }

  void swap(scoped_nsprotocol& that) {
    NST temp = that.object_;
    that.object_ = object_;
    object_ = temp;
  }

  NST autorelease() { return [release() autorelease]; }

 private:
  NST object_;

  [[nodiscard]] NST release() {
    NST temp = object_;
    object_ = nil;
    return temp;
  }
};

template <class C>
void swap(scoped_nsprotocol<C>& p1, scoped_nsprotocol<C>& p2) {
  p1.swap(p2);
}

template <class C>
bool operator==(C p1, const scoped_nsprotocol<C>& p2) {
  return p1 == p2.get();
}

template <class C>
bool operator!=(C p1, const scoped_nsprotocol<C>& p2) {
  return p1 != p2.get();
}

template <typename NST>
class scoped_nsobject : public scoped_nsprotocol<NST*> {
 public:
  explicit scoped_nsobject(NST* object = nil) : scoped_nsprotocol<NST*>(object) {}

  scoped_nsobject(const scoped_nsobject<NST>& that) : scoped_nsprotocol<NST*>(that) {}

  template <typename NSU>
  scoped_nsobject(const scoped_nsobject<NSU>& that) : scoped_nsprotocol<NST*>(that) {}

  scoped_nsobject& operator=(const scoped_nsobject<NST>& that) {
    scoped_nsprotocol<NST*>::operator=(that);
    return *this;
  }
};

template <>
class scoped_nsobject<id> : public scoped_nsprotocol<id> {
 public:
  explicit scoped_nsobject(id object = nil) : scoped_nsprotocol<id>(object) {}

  scoped_nsobject(const scoped_nsobject<id>& that) : scoped_nsprotocol<id>(that) {}

  template <typename NSU>
  scoped_nsobject(const scoped_nsobject<NSU>& that) : scoped_nsprotocol<id>(that) {}

  scoped_nsobject& operator=(const scoped_nsobject<id>& that) {
    scoped_nsprotocol<id>::operator=(that);
    return *this;
  }
};

template <>
class scoped_nsobject<NSAutoreleasePool> {
 private:
  explicit scoped_nsobject(NSAutoreleasePool* object = nil);
  REZERO_DISALLOW_COPY_AND_ASSIGN(scoped_nsobject);
};

} // namespace rezero

#endif // REZERO_BASE_IOS_SCOPED_NSOBJECT_H_
