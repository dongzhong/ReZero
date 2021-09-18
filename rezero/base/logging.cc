// Created by Dong Zhong on 2021/09/13.

#include "rezero/base/logging.h"

#include <algorithm>
#include <iostream>

#include "rezero/base/build_config.h"
#include "rezero/base/log_settings.h"

#if defined(REZERO_PLATFORM_ANDROID)
#include <android/log.h>
#elif defined(REZERO_PLATFORM_IOS)
#include <syslog.h>
#endif

namespace rezero {

namespace {

const char* kLogSeverityNames[LOG_NUM_SEVERITIES] = {
    "INFO",
    "WARNING",
    "ERROR",
    "FATAL"
};

const char* GetNameForLogSeverity(LogSeverity severity) {
  if (severity >= LOG_INFO && severity < LOG_NUM_SEVERITIES) {
    return kLogSeverityNames[severity];
  }
  return "UNKNOWN";
}

const char* StripDots(const char* path) {
  while (strncmp(path, "../", 3) == 0) {
    path += 3;
  }
  return path;
}

const char* StripPath(const char* path) {
  auto* p = strrchr(path, '/');
  if (p) {
    return p + 1;
  }
  return path;
}

} // namespace

LogMessage::LogMessage(LogSeverity severity,
                       const char* file_name,
                       int line,
                       const char* condition)
    : severity_(severity), file_name_(file_name), line_(line) {
  stream_ << "[";
  if (severity_ >= LOG_INFO) {
    stream_ << GetNameForLogSeverity(severity);
  } else {
    stream_ << "VERBOSE" << -severity_;
  }
  stream_ << ":" << (severity > LOG_INFO ? StripDots(file_name_) : StripPath(file_name_))
          << "(" << line_ << ")] ";

  if (condition) {
    stream_ << "Check failed: " << condition << ". ";
  }
}

LogMessage::~LogMessage() {
  stream_ << std::endl;

#if defined(REZERO_PLATFORM_ANDROID)
  android_LogPriority log_priority =
      (severity_ < 0) ? ANDROID_LOG_VERBOSE : ANDROID_LOG_UNKNOWN;
  switch (severity_) {
    case LOG_INFO:
      log_priority = ANDROID_LOG_INFO;
      break;
    case LOG_WARNING:
      log_priority = ANDROID_LOG_WARN;
      break;
    case LOG_ERROR:
      log_priority = ANDROID_LOG_ERROR;
      break;
    case LOG_FATAL:
      log_priority = ANDROID_LOG_FATAL;
      break;
  }
  __android_log_write(log_priority, "rezero", stream_.str().c_str());
#elif defined(REZERO_PLATFORM_IOS)
  syslog(LOG_ALERT, "%s", stream_.str().c_str());
#else
  std::cerr << stream_.str();
  std::cerr.flush();
#endif

  if (severity_ >= LOG_FATAL) {
    KillProcess();
  }
}

int GetVlogVerbosity() {
  return std::max(-1, LOG_INFO - GetMinLogLevel());
}

bool ShouldCreateLogMessage(LogSeverity severity) {
  return severity >= GetMinLogLevel();
}

void KillProcess() {
  abort();
}

} // namespace rezero
