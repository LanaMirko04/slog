/**
 * @file slog.c
 * @date 2023-05-30
 * @author Mirko Lana [lana.mirko@icloud.com]
 * @brief SLog (Sh*tty Logging) library.
 */

#include "slog.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

static uint8_t slog_lv;
static pthread_mutex_t slog_mtx;
FILE *_slog_file;

static char *slog_clear_fmt(const char *fmt) {
    char *new_fmt = calloc(strlen(fmt) + 1, 1);
    if (NULL == new_fmt) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; fmt[i]; ++i) {
        if ('\033' == fmt[i]) {
            while ('m' != fmt[i]) {
                ++i;
            }
        } else {
            new_fmt[j++] = fmt[i];
        }
    }

    return new_fmt;
}

static int slog_log_impl(FILE *os, const char *fmt, va_list args) {
    pthread_mutex_lock(&slog_mtx);

    int ret;
    if (!isatty(fileno(os))) {
        char *new_fmt = slog_clear_fmt(fmt);
        ret = vfprintf(os, new_fmt, args);
        free(new_fmt);
    } else {
        ret = vfprintf(os, fmt, args);
    }

    pthread_mutex_unlock(&slog_mtx);

    return ret;
}

void slog_init(uint8_t lv) {
    _slog_file = NULL;
    slog_lv = lv;
}

int slog_open_file(const char *filepath) {
    if (!filepath) {
        return ERR;
    }

    if (_slog_file) {
        return ERR;
    }

    _slog_file = fopen(filepath, "a");
    if (NULL == _slog_file) {
        return ERR;
    }

    return OK;
}

void slog_close_file(void) {
    if (NULL != _slog_file) {
        fclose(_slog_file);
        _slog_file = NULL;
    }
}

int _slog_log(slog_level_t lv, FILE *os, const char *fmt, ...) {
    if (!(slog_lv & lv) || (NULL == os)) {
        return OK;
    }

    va_list args;
    va_start(args, fmt);

    int ret = slog_log_impl(os, fmt, args);

    va_end(args);

    return ret;
}

int _slog_log_all(slog_level_t lv, const char *fmt, ...) {
    if (!(slog_lv & lv)) {
        return OK;
    }

    va_list args;
    va_start(args, fmt);

    int ret = slog_log_impl((LV_ERROR == lv) ? stderr : stdout, fmt, args);
    if (ERR == ret) {
        va_end(args);
        return ERR;
    }

    if (NULL == _slog_file) {
        va_end(args);
        return ret;
    }

    ret = slog_log_impl(_slog_file, fmt, args);
    if (ERR == ret) {
        va_end(args);
        return ERR;
    }

    va_end(args);

    return ret;
}

char *_slog_get_time(void) {
    static char time_buff[_SLOG_TIME_BUFF_SIZE];
    time_t now = time(NULL);
    struct tm *ltime = localtime(&now);

    bzero(time_buff, _SLOG_TIME_BUFF_SIZE);
    strftime(time_buff, _SLOG_TIME_BUFF_SIZE, "%Y-%m-%d %H:%M:%S", ltime);

    return time_buff;
}
