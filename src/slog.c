/*
 * SLog (Shitty Logging) - slog.h
 * (c) 2023 Lana Mirko
 *
 * */

/* ANSI C headers */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <errno.h>
#include <string.h>
/* POSIX headers */
#include <unistd.h>
/* Local headers */
#include "slog.h"

/*
 * Global variables for controlling logging behavior.
 */
FILE *__log_file = NULL;
int __log_level = { 0 };

/*
 * Function to initialize the logging system.
 * If path is not NULL, it will open a file to log to.
 * If debug is true, it will print debug messages.
 *
 * Parameters:
 *   - path: path to the log file.
 *   - log_level: log level (INFO, DEBUG, WARNING, ERROR).
 *
 */
void __slog_init(const char *path, int log_level) {
  if (path != NULL) {
    __slog_open_file(path);
  }

  __log_level = log_level;
}

/*
 * Function to close the log file.
 * It is called automatically when the program exits.
 *
 * Parameters:
 *   - path: path to the log file.
 */
void __slog_close_file(void) {
  if (__log_file != NULL) {
    fclose(__log_file);
    __log_file = NULL;
  }
}

/*
 * Function to open the log file at the specified path.
 *
 * Parameters:
 *   - path: path to the log file.
 */
void __slog_open_file(const char *path) {
  if (__log_file != NULL)
    return;

  __log_file = fopen(path, "w");
  if (__log_file == NULL) {
    fprintf(stderr, "I can't open '%s': %s", path, strerror(errno));
    exit(EXIT_FAILURE);
  }

  atexit(__slog_close_file);
}

/*
 * Function to log a message at the specified log level.
 *
 * Parameters:
 *   - level: The log level (INFO, DEBUG, WARNING, ERROR).
 *   - format: The format string for the log message.
 *   - ...: Additional parameters to be formatted into the message.
 */
void __slog_log(enum slog_level_e level, char *format, ...) {
  va_list args;
  va_start(args, format);
  _Bool use_file = __log_file != NULL;
  _Bool use_color = !isatty(fileno(stdout));
  char *clean_format = NULL;

  if (use_file || use_color) {
    clean_format = __slog_remove_color(format);
  }

  switch (level) {
    case LV_INFO:
      if (__log_level & LV_INFO) {
        vfprintf(use_file ? __log_file : stdout,
            use_file || use_color ? clean_format  : format, args);
      }
      break;

    case LV_WARN:
      if (__log_level & LV_WARN) {
        vfprintf(use_file ? __log_file : stdout,
            use_file || use_color ? clean_format  : format, args);
      }
      break;

    case LV_DEBUG:
      if (__log_level & LV_DEBUG) {
        vfprintf(use_file ? __log_file : stdout,
            use_file || use_color ? clean_format  : format, args);
      }
      break;

    case LV_ERROR:
      if (__log_level & LV_ERROR) {
        vfprintf(use_file ? __log_file : stderr,
            use_file || use_color ? clean_format  : format, args);
      }
      break;

    case LV_ALL:
    default:
      break;
  }

  if (clean_format != NULL) {
    free(clean_format);
  }

  va_end(args);
}

/*
 * Function to remove ANSI color codes from a string.
 *
 * Parameters:
 *   - str: The input string containing color codes.
 *
 * Returns:
 *   A new string with color codes removed.
 */
char* __slog_remove_color(char *str) {
  char *clean_str = malloc(strlen(str) + 1);
  int i = 0, j = 0;

  while (str[i] != '\0') {
    if (str[i] == '\033') {
      while (str[i] != 'm')
        i++;
    } else {
      clean_str[j] = str[i];
      j++;
    }
    i++;
  }
  clean_str[j] = '\0';

  return clean_str;
}
