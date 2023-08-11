/*
 * SLog (Shitty Logging) - slog.h
 * (c) 2023 Lana Mirko
 *
 * */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>

#include "slog.h"

FILE *_log_file = NULL;
bool _print_debug;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void _slog_init(const char *path, bool debug) {
  if (path != NULL)
    _slog_open_file(path);

  _print_debug = debug;
}

void _slog_close_file() {
  if (_log_file != NULL) {
    fclose(_log_file);
    _log_file = NULL;
  }
}

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

void _slog_log(enum _slog_level_e level, const char *format, ...) {
  va_list args;
  va_start(args, format);

  pthread_mutex_lock(&mutex);

  switch (level) {
    case _INFO:
      vfprintf(_log_file == NULL ? stdout : _log_file, format, args);
      break;

    case _DEBUG:
      if (_print_debug)
        vfprintf(_log_file == NULL ? stdout : _log_file, format, args);
      break;

    case _WARNING:
      vfprintf(_log_file == NULL ? stdout : _log_file, format, args);
      break;

    case _ERROR:
      vfprintf(_log_file == NULL ? stderr : _log_file, format, args);
      break;
  }

  pthread_mutex_unlock(&mutex);

  va_end(args);
}
