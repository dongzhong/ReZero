// Created by Dong Zhong on 2021/09/14.

#include "rezero/base/thread_local.h"

#include "rezero/base/logging.h"

namespace rezero {

namespace internal {

ThreadLocalPointer::ThreadLocalPointer(void (*destroy)(void *)) {
  REZERO_CHECK(pthread_key_create(&key_, destroy) == 0);
}

ThreadLocalPointer::~ThreadLocalPointer() {
  REZERO_CHECK(pthread_key_delete(key_) == 0);
}

void* ThreadLocalPointer::get() const {
  return pthread_getspecific(key_);
}

void* ThreadLocalPointer::swap(void *ptr) {
  void* old_ptr = get();
  REZERO_CHECK(pthread_setspecific(key_, ptr) == 0);
  return old_ptr;
}

} // namespace internal

} // namespace rezero