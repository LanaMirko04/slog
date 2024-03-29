/*
 * SLog (Shitty Logging) - slog.h
 * (c) 2023 Lana Mirko
 *
 */

#ifndef __SLOG_H__
#define __SLOG_H__

#include <stdio.h>
#include "colors.h"

/*
 * Enumeration representing different log levels.
 */
enum slog_level_e {
  LV_INFO   = 0x01,
  LV_DEBUG  = 0x02,
  LV_WARN   = 0x04,
  LV_ERROR  = 0x08,
  LV_ALL    = 0x0F
};

/*
 * Global variables / for controlling logging behavior.
 */
extern FILE *__log_file;
extern int __log_level;

/*
 * Macro to initialize the logging system.
 *
 * Parameters:
 *   - path: The path to the log file.
 *   - debug: A boolean indicating whether to print debug messages.
 */
#define SLOG_INIT(path, log_level) __slog_init(path, log_level)

/*
 * Macros for logging messages at different levels.
 *
 * Parameters:
 *   - message: The format string for the log message.
 *   - ...: Additional parameters to be formatted into the message.
 */
#define SLOG_INFO(message, ...) \
  __slog_log(LV_INFO, BOLD GREEN "[INFO]" RESET " %s:%d -> " message "\n", \
      __FILE__, __LINE__ __VA_OPT__(,) __VA_ARGS__)
#define SLOG_DEBUG(message, ...) \
  __slog_log(LV_DEBUG, BOLD BLUE "[DEBUG]" RESET " %s:%d -> " message "\n", \
      __FILE__, __LINE__ __VA_OPT__(,) __VA_ARGS__)
#define SLOG_WARN(message, ...) \
  __slog_log(LV_WARN, BOLD YELLOW "[WARNING]" RESET " %s:%d -> " message "\n", \
      __FILE__, __LINE__ __VA_OPT__(,) __VA_ARGS__)
#define SLOG_ERROR(message, ...) \
  __slog_log(LV_ERROR, BOLD RED "[ERROR]" RESET " %s:%d -> " message "\n", \
      __FILE__, __LINE__ __VA_OPT__(,) __VA_ARGS__)

/*
 * Function to initialize the logging system.
 *
 * Parameters:
 *   - path: The path to the log file.
 *   - log_level: log level (INFO, DEBUG, WARNING, ERROR).
 */
extern void __slog_init(const char *path, int log_level);

/*
 * Function to close the log file.
 */
extern void __slog_close_file(void);

/*
 * Function to open the log file at the specified path.
 *
 * Parameters:
 *   - path: The path to the log file.
 */
extern void __slog_open_file(const char *path);

/*
 * Function to log a message at the specified log level.
 *
 * Parameters:
 *   - level: The log level (INFO, DEBUG, WARNING, ERROR).
 *   - format: The format string for the log message.
 *   - ...: Additional parameters to be formatted into the message.
 */
extern void __slog_log(enum slog_level_e level, char *format, ...);

/*
 * Function to remove ANSI color codes from a string.
 *
 * Parameters:
 *   - str: The input string containing color codes.
 *
 * Returns:
 *   A new string with color codes removed.
 */
char* __slog_remove_color(char *str);

#endif
