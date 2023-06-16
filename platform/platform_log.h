/**
 * @file
 * @brief Logging part of the Platform API.
 *
 * @note LOG_ARGS and LOG macros should be excluded and defined for
 *       your platform.
 *       Current implementation is included as an example.
 */

#ifndef PLATFORM_LOG_H_
#define PLATFORM_LOG_H_

#ifdef __cplusplus
extern "C" {
#endif

// Logging macros require I/O functions from standard library
#include <stdio.h>
#include <string.h>

// Platform specific implementation.
#define FNAME strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__
#define LOG_ARGS(LOG_MRK)   LOG_MRK, FNAME, __func__, __LINE__
#define LOG(...)    fprintf(stderr, __VA_ARGS__)

// Log levels.
//! Logger message level for error messages.
#define ERR_LVL 1
//! Logger message level for info messages.
#define INF_LVL 2
//! Logger message level for debug messages.
#define DBG_LVL 3

//! Default compile time log level.
#ifndef LOG_LVL
#ifdef DEBUG
#define LOG_LVL DBG_LVL
#else
#define LOG_LVL INF_LVL
#endif // DEBUG
#endif // LOG_LVL

// Log level marks.
//! Logger message mark for an error message.
#define ERR_MRK "E"
//! Logger message mark for an info message.
#define INF_MRK "I"
//! Logger message mark for a debug message.
#define DBG_MRK "D"

//! Convert log level (int) to the corresponding log mark (char).
#define LOG_MARK(LVL) { \
  (LVL == ERR_LVL ? ERR_MRK : \
   (LVL == INF_LVL ? INF_MRK : (LVL == DBG_LVL ? DBG_MRK : UKN_MRK))) \
}

//! Log message format: Log level mark, file name, function, line number.
#define LOG_FMT "%s | %-15s | %s:%d | "

//! Generate a debug level log message.
#if LOG_LVL >= DBG_LVL
#define DLOG(...)  LOG(LOG_FMT, LOG_ARGS(DBG_MRK)); LOG(__VA_ARGS__); LOG("\n");
#else
#define DLOG(...)
#endif

//! Generate an info level log message.
#if LOG_LVL >= INF_LVL
#define ILOG(...) LOG(LOG_FMT, LOG_ARGS(INF_MRK)); LOG(__VA_ARGS__); LOG("\n");
#else
#define ILOG(...)
#endif

//! Generate an error level log message.
#if LOG_LVL >= ERR_LVL
#define ELOG(...) LOG(LOG_FMT, LOG_ARGS(ERR_MRK)); LOG(__VA_ARGS__); LOG("\n");
#else
#define ELOG(...)
#endif

#ifdef __cplusplus
}
#endif

#endif // PLATFORM_LOG_H_
