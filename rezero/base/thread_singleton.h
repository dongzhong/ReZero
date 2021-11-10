// Created by Dong Zhong on 2021/10/29.

#ifndef REZERO_BASE_THREAD_SINGLETON_H_
#define REZERO_BASE_THREAD_SINGLETON_H_

#include "rezero/base/logging.h"
#include "rezero/base/thread_local.h"

namespace rezero {

template <typename T>
class ThreadSingleton {
 public:
  template <typename... Args>
  static void EnsureInitializedForCurrentThread(Args&&... args) {
    if (tls_singleton_.get() != nullptr) {
      // Already initialized.
      return;
    }
    tls_singleton_.reset(new T(std::forward<Args>(args)...));
  }

  static bool IsInitializedForCurrentThread() {
    return tls_singleton_.get() != nullptr;
  }

  static T& GetCurrent() {
    auto* singleton = tls_singleton_.get();
    REZERO_CHECK(singleton != nullptr)
        << "ThreadSingleton::EnsureInitializedForCurrentThread was not called "
           "on this thread prior to singleton use.";
    return *singleton;
  }

  ~ThreadSingleton() = default;

 protected:
  ThreadSingleton() = default;

 private:
  static ThreadLocalUniquePtr<T> tls_singleton_;

  REZERO_DISALLOW_COPY_AND_ASSIGN(ThreadSingleton);
};

template <typename T>
ThreadLocalUniquePtr<T> ThreadSingleton<T>::tls_singleton_;

} // namespace rezero

#endif // REZERO_BASE_THREAD_SINGLETON_H_
