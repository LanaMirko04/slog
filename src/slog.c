/*
 * SLog (Shitty Logging) - slog.h
 * (c) 2023 Lana Mirko
 *
 * */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <errno.h>
#include <string.h>

#include "slog.h"

FILE *_log_file = NULL;

void _slog_close_file() {
  if (_log_file != NULL) {
    fclose(_log_file);
    _log_file = NULL;
    SLOG_DEBUG("'slog.log' closed successfully!");
  }
}

void _slog_open_file() {
  if (_log_file != NULL)
    return;

  SLOG_DEBUG("Opening 'slog.log'...");
  _log_file = fopen("slog.log", "w");
  if (_log_file == NULL) {
    SLOG_ERROR("I can't open 'slog.log': %s", strerror(errno));
    exit(EXIT_FAILURE);
  }
  SLOG_DEBUG("'slog.log' opened successfully!");

  atexit(_slog_close_file);
}

void _slog_log(enum _slog_level_e level, const char *format, ...) {
  va_list args;
  va_start(args, format);

  switch (level) {
    case _INFO:
      vfprintf(_log_file == NULL ? stdout : _log_file, format, args);
      break;

    case _DEBUG:
      #ifdef _SLOG_DEBUG
        vfprintf(_log_file == NULL ? stdout : _log_file, format, args);
      #endif /* DEBUG */
      break;

    case _WARNING:
      vfprintf(_log_file == NULL ? stdout : _log_file, format, args);
      break;

    case _ERROR:
      vfprintf(_log_file == NULL ? stderr : _log_file, format, args);
      break;
  }

  va_end(args);
}
