/*
 * SLog (Shitty Logging) - slog.h
 * (c) 2023 Lana Mirko
 *
 */

#ifndef __SLOG_H__
#define __SLOG_H__

#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include "colors.h"

/*
 * Enumeration representing different log levels.
 */
enum _slog_level_e {
  _INFO,
  _DEBUG,
  _WARNING,
  _ERROR
};

/*
 * Global variables for controlling logging behavior.
 */
extern FILE *_log_file;
extern bool _print_debug;
extern pthread_mutex_t mutex;

/*
 * Macro to initialize the logging system.
 *
 * Parameters:
 *   - path: The path to the log file.
 *   - debug: A boolean indicating whether to print debug messages.
 */
#define SLOG_INIT(path, debug) _slog_init(path, debug)

/*
 * Macros for logging messages at different levels.
 *
 * Parameters:
 *   - message: The format string for the log message.
 *   - ...: Additional parameters to be formatted into the message.
 */
#define SLOG_INFO(message, ...) \
  _slog_log(_INFO, BOLD GREEN "[INFO]" RESET " %s:%d -> " message "\n", \
      __FILE__, __LINE__, ##__VA_ARGS__)
#define SLOG_DEBUG(message, ...) \
  _slog_log(_DEBUG, BOLD BLUE "[DEBUG]" RESET " %s:%d -> " message "\n", \
      __FILE__, __LINE__, ##__VA_ARGS__)
#define SLOG_WARNING(message, ...) \
  _slog_log(_WARNING, BOLD YELLOW "[WARNING]" RESET " %s:%d -> " message "\n", \
      __FILE__, __LINE__, ##__VA_ARGS__)
#define SLOG_ERROR(message, ...) \
  _slog_log(_ERROR, BOLD RED "[ERROR]" RESET " %s:%d -> " message "\n", \
      __FILE__, __LINE__, ##__VA_ARGS__)

/*
 * Function to initialize the logging system.
 *
 * Parameters:
 *   - path: The path to the log file.
 *   - debug: A boolean indicating whether to print debug messages.
 */
void _slog_init(const char *path, bool debug);

/*
 * Function to close the log file.
 */
void _slog_close_file();

/*
 * Function to open the log file at the specified path.
 *
 * Parameters:
 *   - path: The path to the log file.
 */
void _slog_open_file(const char *path);

/*
 * Function to log a message at the specified log level.
 *
 * Parameters:
 *   - level: The log level (INFO, DEBUG, WARNING, ERROR).
 *   - format: The format string for the log message.
 *   - ...: Additional parameters to be formatted into the message.
 */
void _slog_log(enum _slog_level_e level, char *format, ...);

/*
 * Function to remove ANSI color codes from a string.
 *
 * Parameters:
 *   - str: The input string containing color codes.
 *
 * Returns:
 *   A new string with color codes removed.
 */
char *_slog_remove_color(char *str);

#endif
