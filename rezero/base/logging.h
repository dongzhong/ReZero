// Created by Dong Zhong on 2021/09/13.

#ifndef REZERO_BASE_LOGGING_H_
#define REZERO_BASE_LOGGING_H_

#include <sstream>

#include "rezero/base/log_level.h"
#include "rezero/base/macros.h"

namespace rezero {

class LogMessageVoidify {
 public:
  void operator&(std::ostream&) {}
};

class LogMessage {
 public:
  LogMessage(LogSeverity severity,
             const char* file_name,
             int line,
             const char* condition);

  ~LogMessage();

  std::ostream& stream() { return stream_; }

 private:
  std::ostringstream stream_;
  const LogSeverity severity_;
  const char* file_name_;
  const int line_;

  REZERO_DISALLOW_COPY_AND_ASSIGN(LogMessage);
};

int GetVlogVerbosity();

bool ShouldCreateLogMessage(LogSeverity severity);

[[noreturn]] void KillProcess();

} // namespace rezero

#define REZERO_LOG_STREAM(severity) \
  ::rezero::LogMessage(::rezero::LOG_##severity, __FILE__, __LINE__, nullptr).stream()

#define REZERO_LAZY_STREAM(stream, condition) \
  !(condition) ? (void)0 : ::rezero::LogMessageVoidify() & (stream)

#define REZERO_EAT_STREAM_PARAMETERS(ignored) \
  true || (ignored)                           \
      ? (void)0                               \
      : ::rezero::LogMessageVoidify() &       \
            ::rezero::LogMessage(::rezero::LOG_FATAL, 0, 0, nullptr).stream()

#define REZERO_LOG_IS_ON(severity) \
  (::rezero::ShouldCreateLogMessage(::rezero::LOG_##severity))

#define REZERO_LOG(severity) \
  REZERO_LAZY_STREAM(REZERO_LOG_STREAM(severity), REZERO_LOG_IS_ON(severity))

#define REZERO_CHECK(condition)                                                 \
  REZERO_LAZY_STREAM(                                                           \
      ::rezero::LogMessage(::rezero::LOG_FATAL, __FILE__, __LINE__, #condition) \
          .stream(),                                                            \
      !(condition))

#define REZERO_VLOG_IS_ON(verbose_level) \
  ((verbose_level) <= ::rezero::GetVlogVerbosity())

#define REZERO_VLOG_STREAM(verbose_level) \
  ::rezero::LogMessage(-verbose_level, __FILE__, __LINE__, nullptr).stream()

#define REZERO_VLOG(verbose_level) \
  REZERO_LAZY_STREAM(REZERO_VLOG_STREAM(verbose_level), REZERO_VLOG_IS_ON(verbose_level))

#ifndef NDEBUG
#define REZERO_DLOG(severity) REZERO_LOG(severity)
#define REZERO_DCHECK(condition) REZERO_CHECK(condition)
#else
#define REZERO_DLOG(severity) REZERO_EAT_STREAM_PARAMETERS(true)
#define REZERO_DCHECK(condition) REZERO_EAT_STREAM_PARAMETERS(condition)
#endif

#define REZERO_UNREACHABLE()                          \
  {                                                   \
    REZERO_LOG(ERROR) << "Reached unreachable code."; \
    ::rezero::KillProcess();                          \
  }

#endif // REZERO_BASE_LOGGING_H_