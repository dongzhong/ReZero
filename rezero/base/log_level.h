// Created by Dong Zhong on 2021/09/13.

#ifndef REZERO_BASE_LOG_LEVEL_H_
#define REZERO_BASE_LOG_LEVEL_H_

namespace rezero {

typedef int LogSeverity;

constexpr LogSeverity LOG_INFO = 0;
constexpr LogSeverity LOG_WARNING = 1;
constexpr LogSeverity LOG_ERROR = 2;
constexpr LogSeverity LOG_FATAL = 3;
constexpr LogSeverity LOG_NUM_SEVERITIES = 4;

#ifdef NDEBUG
const LogSeverity LOG_DFATAL = LOG_ERROR;
#else
const LogSeverity LOG_DFATAL = LOG_FATAL;
#endif

} // namespace rezero

#endif // REZERO_BASE_LOG_LEVEL_H_