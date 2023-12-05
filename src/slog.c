/*
 * SLog (Shitty Logging) - slog.h
 * (c) 2023 Lana Mirko
 *
 * */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>

#include "slog.h"

/*
 * Global variables for controlling logging behavior.
 */
FILE *_log_file = NULL;
int _log_level = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

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
void _slog_init(const char *path, int log_level) {
  if (path != NULL)
    _slog_open_file(path);

  _log_level = log_level;
}

/*
 * Function to close the log file.
 * It is called automatically when the program exits.
 *
 * Parameters:
 *   - path: path to the log file.
 */
void _slog_close_file(void) {
  if (_log_file != NULL) {
    fclose(_log_file);
    _log_file = NULL;
  }
}

/*
 * Function to open the log file at the specified path.
 *
 * Parameters:
 *   - path: path to the log file.
 */
void _slog_open_file(const char *path) {
  if (_log_file != NULL)
    return;

  SLOG_DEBUG("Opening '%s'...", path);
  _log_file = fopen(path, "w");
  if (_log_file == NULL) {
    SLOG_ERROR("I can't open '%s': %s", path, strerror(errno));
    exit(EXIT_FAILURE);
  }
  SLOG_DEBUG("'%s' opened successfully!", path);

  atexit(_slog_close_file);
}

/*
 * Function to log a message at the specified log level.
 *
 * Parameters:
 *   - level: The log level (INFO, DEBUG, WARNING, ERROR).
 *   - format: The format string for the log message.
 *   - ...: Additional parameters to be formatted into the message.
 */
void _slog_log(enum slog_level_e level, char *format, ...) {
  va_list args;
  va_start(args, format);
  bool use_file = _log_file != NULL;
  bool use_color = !isatty(fileno(stdout));
  char *clean_format = NULL;

  pthread_mutex_lock(&mutex);

  if (use_file || use_color) {
    clean_format = _slog_remove_color(format);
  }

  switch (level) {
    case INFO:
      if (_log_level & INFO) {
        vfprintf(use_file ? _log_file : stdout,
            use_file || use_color ? clean_format  : format, args);
      }
      break;

    case WARNING:
      if (_log_level & WARNING) {
        vfprintf(use_file ? _log_file : stdout,
            use_file || use_color ? clean_format  : format, args);
      }
      break;

    case DEBUG:
      if (_log_level & DEBUG) {
        vfprintf(use_file ? _log_file : stdout,
            use_file || use_color ? clean_format  : format, args);
      }
      break;

    case ERROR:
      if (_log_level & ERROR) {
        vfprintf(use_file ? _log_file : stderr,
            use_file || use_color ? clean_format  : format, args);
      }
      break;
  }

  if (clean_format != NULL) {
    free(clean_format);
  }

  pthread_mutex_unlock(&mutex);

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
char *_slog_remove_color(char *str) {
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
