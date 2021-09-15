// Created by Dong Zhong on 2021/09/14.

#ifndef REZERO_BASE_THREAD_LOCAL_H_
#define REZERO_BASE_THREAD_LOCAL_H_

#include <pthread.h>

#include "rezero/base/macros.h"

namespace rezero {

namespace internal {

class ThreadLocalPointer {
 public:
  ThreadLocalPointer(void (*destroy)(void*));
  ~ThreadLocalPointer();

  void* get() const;
  void* swap(void* ptr);

 private:
  pthread_key_t key_;

  REZERO_DISALLOW_COPY_AND_ASSIGN(ThreadLocalPointer);
};

} // namespace internal

template <typename T>
class ThreadLocalUniquePtr {
 public:
  ThreadLocalUniquePtr() : ptr_(destroy) {}

  T* get() const { return reinterpret_cast<T*>(ptr_.get()); }
  void reset(T* ptr) { destroy(ptr_.swap(ptr)); }

 private:
  static void destroy(void* ptr) { delete reinterpret_cast<T*>(ptr); }

  internal::ThreadLocalPointer ptr_;

  REZERO_DISALLOW_COPY_AND_ASSIGN(ThreadLocalUniquePtr);
};

} // namespace rezero

#endif // REZERO_BASE_THREAD_LOCAL_H_