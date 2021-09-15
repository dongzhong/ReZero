// Created by Dong Zhong on 2021/09/14.

#ifndef REZERO_BASE_THREAD_H_
#define REZERO_BASE_THREAD_H_

#include <thread>

#include "rezero/base/macros.h"
#include "rezero/base/task_runner.h"

namespace rezero {

class Thread {
 public:
  static void SetCurrentThreadName(const std::string& name);

  explicit Thread(const std::string& thread_name = "");

  ~Thread();

  std::shared_ptr<TaskRunner> GetTaskRunner() const;

 private:
  std::unique_ptr<std::thread> thread_;
  std::shared_ptr<TaskRunner> task_runner_;
};

} // namespace rezero

#endif //REZERO_BASE_THREAD_H_
