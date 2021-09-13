// Created by Dong Zhong on 2021/09/13.

#ifndef REZERO_BASE_LOG_SETTING_H_
#define REZERO_BASE_LOG_SETTING_H_

#include "rezero/base/log_level.h"

namespace rezero {

struct LogSettings {
  LogSeverity min_log_level = LOG_INFO;
};

void SetLogSettings(const LogSettings& settings);

LogSettings GetLogSettings();

LogSeverity GetMinLogLevel();

class ScopedSetLogSettings {
 public:
  ScopedSetLogSettings(const LogSettings& settings);
  ~ScopedSetLogSettings();

 private:
  LogSettings old_settings_;
};

} // namespace rezero

#endif // REZERO_BASE_LOG_SETTING_H_