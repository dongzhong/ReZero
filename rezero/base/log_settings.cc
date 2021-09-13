// Created by Dong Zhong on 2021/09/13.

#include "rezero/base/log_settings.h"

#include <algorithm>

namespace rezero {
namespace state {

extern LogSettings g_log_settings;

} // namespace state

void SetLogSettings(const LogSettings& settings) {
  state::g_log_settings.min_log_level =
      std::min(LOG_FATAL, settings.min_log_level);
}

LogSettings GetLogSettings() {
  return state::g_log_settings;
}

LogSeverity GetMinLogLevel() {
  return std::min(state::g_log_settings.min_log_level, LOG_FATAL);
}

ScopedSetLogSettings::ScopedSetLogSettings(const LogSettings& settings) {
  old_settings_ = GetLogSettings();
  SetLogSettings(settings);
}

ScopedSetLogSettings::~ScopedSetLogSettings() {
  SetLogSettings(old_settings_);
}


} // namespace rezero