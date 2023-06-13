/**
 * @file
 *
 * @brief A set of macros with quick checks.
 *
 * @details Macros to perform a check and if it does not pass
 *        an error message to be generated using a logging API.
 *
 * @note ASSERT to be excluded and implemented per platform.
 *       Current implementation is included as an example.
 */

#ifndef PLATFORM_CHECK_H_
#define PLATFORM_CHECK_H_

#include "platform_log.h"

#include <assert.h>

#ifdef __cplusplus
extern "C" {
#endif

// Platform specific implementation.
#define ASSERT(val) assert(val)

/**
 * @brief Quick chekck if an expression is true.
 *
 * @details
 * Evaluates and checks if an expression is true. If not, prints
 * an error message msg+args with @ref ELOG and asserts with @ref ASSERT.
 *
 * @see ASSERT
 * @see ELOG
 *
 * Example:
 * ```
 *   int buf_bytes = 1024;
 *   char* buf = malloc(buf_bytes);
 *   QCHECK(buf != NULL, "Unable to allocate %d bytes", buf_bytes);
 * ```
 *
 * @param expr An expression that should be evaluated as true.
 * @param msg A formatted message to print when check fails.
 * @param args Arguments for the formatted message.
 *
 * @return void
 */
#define QCHECK(expr, ...)                          \
  do {                                             \
    if (!(expr)) {                                 \
      LOG(LOG_FMT, LOG_ARGS(ERR_MRK));             \
      LOG("QCHECK failed. ");                      \
      LOG(__VA_ARGS__); LOG("\n");                 \
      ASSERT(false);                               \
    }                                              \
  } while (false)

/**
 * @brief Quick check if lh == rh.
 *
 * @details
 * Checks if 2 variabels are equal. If not, prints an error message
 * msg+args with @ref ELOG and asserts with @ref ASSERT.
 *
 * Example:
 * ```
 *   int written = fwrite(buf, 1, to_write, fp);
 *   QCHECK_EQ(to_write, written, "%d",
 *             "Failed to write buffer to file %s", name);
 * ```
 *
 * @param lh A first variable to check for equity.
 * @param rh A second variable to check for equity.
 * @param fmt A variable format when printed.
 * @param msg A formatted message to print when check fails.
 * @param args Arguments for the formatted message.
 *
 * @return void
 */
#define QCHECK_EQ(lh, rh, fmt, ...)                                            \
  do {                                                                         \
    if (!((lh) == (rh))) {                                                     \
      LOG(LOG_FMT, LOG_ARGS(ERR_MRK));                                         \
      LOG("QCHECK failed: " #lh " (" fmt ") == " #rh " (" fmt "). ", lh, rh);  \
      LOG(__VA_ARGS__); LOG("\n");                                             \
      ASSERT(false);                                                           \
    }                                                                          \
  } while (false)

/**
 * @brief Quick check if lh != rh.
 *
 * @details
 * Checks if 2 variabels are not equal. Otherwise, prints an
 * error message msg+args with @ref ELOG and asserts with @ref ASSERT.
 *
 * Example:
 * ```
 * ```
 *
 * @param lh A first variable to check for equity.
 * @param rh A second variable to check for equity.
 * @param fmt A variable format when printed.
 * @param msg A formatted message to print when check fails.
 * @param args Arguments for the formatted message.
 *
 * @return void
 */
#define QCHECK_NE(lh, rh, fmt,  ...)                                           \
  do {                                                                         \
    if (!((lh) != (rh))) {                                                     \
      LOG(LOG_FMT, LOG_ARGS(ERR_MRK));                                         \
      LOG("QCHECK failed: " #lh " (" fmt ") != " #rh " (" fmt "). ", lh, rh);  \
      LOG(__VA_ARGS__); LOG("\n");                                             \
      ASSERT(false);                                                           \
    }                                                                          \
  } while (false)

/**
 * @brief Quick check if lh < rh.
 *
 * @details
 * Checks if a first variable is less than a second. Otherwise,
 * prints an error message msg+args with @ref ELOG and asserts with @ref ASSERT.
 *
 * Example:
 * ```
 * ```
 *
 * @param lh A first variable to check.
 * @param rh A second variable to check.
 * @param fmt A variable format when printed.
 * @param msg A formatted message to print when check fails.
 * @param args Arguments for the formatted message.
 *
 * @return void
 */
#define QCHECK_LT(lh, rh, fmt, ...)                                            \
  do {                                                                         \
    if (!((lh) < (rh))) {                                                      \
      LOG(LOG_FMT, LOG_ARGS(ERR_MRK));                                         \
      LOG("QCHECK failed: " #lh " (" fmt ") < " #rh " (" fmt "). ", lh, rh);   \
      LOG(__VA_ARGS__); LOG("\n");                                             \
      ASSERT(false);                                                           \
    }                                                                          \
  } while (false)

/**
 * @brief Quick check if lh <= rh.
 *
 * @details
 * Checks if a first variable is less or equal to a second. Otherwise,
 * prints an error message msg+args with @ref ELOG and asserts with @ref ASSERT.
 *
 * Example:
 * ```
 * ```
 *
 * @param lh A first variable to check.
 * @param rh A second variable to check.
 * @param fmt A variable format when printed.
 * @param msg A formatted message to print when check fails.
 * @param args Arguments for the formatted message.
 *
 * @return void
 */
#define QCHECK_LE(lh, rh, fmt, ...)                                            \
  do {                                                                         \
    if (!((lh) <= (rh))) {                                                     \
      LOG(LOG_FMT, LOG_ARGS(ERR_MRK));                                         \
      LOG("QCHECK failed: " #lh " (" fmt ") <= " #rh " (" fmt "). ", lh, rh);  \
      LOG(__VA_ARGS__); LOG("\n");                                             \
      ASSERT(false);                                                           \
    }                                                                          \
  } while (false)

/**
 * @brief Quick check if lh > rh.
 *
 * @details
 * Checks if a first variable is greater to a second. Otherwise,
 * prints an error message msg+args with @ref ELOG and asserts with @ref ASSERT.
 *
 * Example:
 * ```
 * ```
 *
 * @param lh A first variable to check.
 * @param rh A second variable to check.
 * @param fmt A variable format when printed.
 * @param msg A formatted message to print when check fails.
 * @param args Arguments for the formatted message.
 *
 * @return void
 */
#define QCHECK_GT(lh, rh, fmt, ...)                                            \
  do {                                                                         \
    if (!((lh) > (rh))) {                                                      \
      LOG(LOG_FMT, LOG_ARGS(ERR_MRK));                                         \
      LOG("QCHECK failed: " #lh " (" fmt ") > " #rh " (" fmt "). ", lh, rh);   \
      LOG(__VA_ARGS__); LOG("\n");                                             \
      ASSERT(false);                                                           \
    }                                                                          \
  } while (false)

/**
 * @brief Quick check if lh >= rh.
 *
 * @details
 * Checks if a first variable is greater or equal to a second. Otherwise,
 * prints an error message msg+args with @ref ELOG and asserts with @ref ASSERT.
 *
 * Example:
 * ```
 * ```
 *
 * @param lh A first variable to check.
 * @param rh A second variable to check.
 * @param fmt A variable format when printed.
 * @param msg A formatted message to print when check fails.
 * @param args Arguments for the formatted message.
 *
 * @return void
 */
#define QCHECK_GE(lh, rh, fmt, ...)                                            \
  do {                                                                         \
    if (!((lh) >= (rh))) {                                                     \
      LOG(LOG_FMT, LOG_ARGS(ERR_MRK));                                         \
      LOG("QCHECK failed: " #lh " (" fmt ") >= " #rh " (" fmt "). ", lh, rh);  \
      LOG(__VA_ARGS__); LOG("\n");                                             \
      ASSERT(false);                                                           \
    }                                                                          \
  } while (false)

#ifdef __cplusplus
}
#endif

#endif // PLATFORM_CHECK_H_
