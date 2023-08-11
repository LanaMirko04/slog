/*
 * SLog (Shitty Logging) - slog.h
 * (c) 2023 Lana Mirko
 *
 * */

#ifndef __SLOG_H__
#define __SLOG_H__

#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include "colors.h"

enum _slog_level_e {
  _INFO,
  _DEBUG,
  _WARNING,
  _ERROR
};

extern FILE *_log_file;
extern bool _print_debug;
extern pthread_mutex_t mutex;

#define SLOG_INIT(path, debug) _slog_init(path, debug)
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


void _slog_init(const char *path, bool debug);
void _slog_close_file();
void _slog_open_file(const char *path);
void _slog_log(enum _slog_level_e level, const char *format, ...);

#endif
