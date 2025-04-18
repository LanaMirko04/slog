/**
 * @file slog.h
 * @date 2023-05-30
 * @author Mirko Lana [lana.mirko@icloud.com]
 * @brief SLog (Sh*tty Logging) library.
 */

#ifndef __SLOG_H__
#define __SLOG_H__

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <stdio.h>
#include <stdint.h>
#include <time.h>

#ifndef ERR
#define ERR -1 ///< Error return value.
#endif // ERR

#ifndef OK
#define OK 0 ///< Success return value.
#endif // OK

#define _SLOG_TIME_BUFF_SIZE ((size_t)0x14) ///< Size of the time string.

/**
 * @brief Enumeration representing different log levels.
 */
typedef enum {
    LV_NONE = 0x00,     ///< No logging messages.
    LV_INFO = 0x01,     ///< Informational messages.
    LV_ERROR = 0x02,    ///< Error messages.
    LV_WARN = 0x04,     ///< Warning messages.
    LV_DEBUG = 0x08,    ///< Debugging messages.
    LV_ALL = 0x0F,      ///< All messages.
} slog_level_t;

extern FILE *_slog_file; ///< Pointer to the current opened log file.

/**
 * @brief Initializes SLog.
 *
 * @param lv The logging level.
 */
void slog_init(uint8_t lv);

/**
 * @brief Opens the log file at the specified path.
 *
 * @param filepath The path to the log file.
 * @return ERR if an error occurs, OK otherwise.
 */
int slog_open_file(const char *filepath);

/**
 * @brief Closes the log file.
 */
void slog_close_file(void);

/**
 * @brief Logs a message at the specified log level to an output stream.
 *
 * @param lv The log level (combination of slog_level_e flags).
 * @param os The output stream.
 * @param fmt The format string for the log message.
 * @param ... Additional parameters to be formatted into the message.
 * @return ERR if an error occurs, the number of bytes written otherwise.
 */
int _slog_log(slog_level_t lv, FILE *os, const char *fmt, ...);

/**
 * @brief Logs a message at the specified log level on every output stream.
 *
 * @param lv The log level (combination of slog_level_e flags).
 * @param fmt The format string for the log message.
 * @param ... Additional parameters to be formatted into the message.
 * @return ERR if an error occurs, the number of bytes written otherwise.
 */
int _slog_log_all(slog_level_t lv, const char *fmt, ...);

/**
 * @brief Gets a string representing time.
 *
 * @return A pointer to a string representing the current time (26 characters
 * long).
 */
char *_slog_get_time(void);

/**
 * @brief Logs an info message to both stdout and the log file.
 */
#define slog_info(fmt, ...)                                                    \
    _slog_log_all(LV_INFO,                                                     \
                  "\033[37m%s\033[0m \033[1;32m[INFO]\033[0m %s:%d -> " fmt    \
                  "\n",                                                        \
                  _slog_get_time(), __FILE__, __LINE__, ##__VA_ARGS__)

/**
 * @brief Logs an error message to both stdout and the log file.
 */
#define slog_error(fmt, ...)                                                   \
    _slog_log_all(LV_ERROR,                                                    \
                  "\033[37m%s\033[0m \033[1;31m[ERROR]\033[0m %s:%d -> " fmt   \
                  "\n",                                                        \
                  _slog_get_time(), __FILE__, __LINE__, ##__VA_ARGS__)

/**
 * @brief Logs an warning message to both stdout and the log file.
 */
#define slog_warn(fmt, ...)                                                    \
    _slog_log_all(LV_WARN,                                                     \
                  "\033[37m%s\033[0m \033[1;33m[WARN]\033[0m %s:%d -> " fmt    \
                  "\n",                                                        \
                  _slog_get_time(), __FILE__, __LINE__, ##__VA_ARGS__)

/**
 * @brief Logs an debug message to both stdout and the log file.
 */
#define slog_debug(fmt, ...)                                                   \
    _slog_log_all(LV_DEBUG,                                                    \
                  "\033[37m%s\033[0m \033[1;34m[DEBUG]\033[0m %s:%d -> " fmt   \
                  "\n",                                                        \
                  _slog_get_time(), __FILE__, __LINE__, ##__VA_ARGS__)

/**
 * @brief Logs an info message to stdout only.
 */
#define slog_info_c(fmt, ...)                                                  \
    _slog_log(LV_INFO, stdout,                                                 \
              "\033[37m%s\033[0m \033[1;32m[INFO]\033[0m %s:%d -> " fmt "\n",  \
              _slog_get_time(), __FILE__, __LINE__, ##__VA_ARGS__)

/**
 * @brief Logs an error message to stdout only.
 */
#define slog_error_c(fmt, ...)                                                 \
    _slog_log(LV_ERROR, stderr,                                                \
              "\033[37m%s\033[0m \033[1;31m[ERROR]\033[0m %s:%d -> " fmt "\n", \
              _slog_get_time(), __FILE__, __LINE__, ##__VA_ARGS__)

/**
 * @brief Logs an warning message to stdout only.
 */
#define slog_warn_c(fmt, ...)                                                  \
    _slog_log(LV_WARN, stdout,                                                 \
              "\033[37m%s\033[0m \033[1;33m[WARN]\033[0m %s:%d -> " fmt "\n",  \
              _slog_get_time(), __FILE__, __LINE__, ##__VA_ARGS__)

/**
 * @brief Logs an debug message to stdout only.
 */
#define slog_debug_c(fmt, ...)                                                 \
    _slog_log(LV_DEBUG, stdout,                                                \
              "\033[37m%s\033[0m \033[1;34m[DEBUG]\033[0m %s:%d -> " fmt "\n", \
              _slog_get_time(), __FILE__, __LINE__, ##__VA_ARGS__)

/**
 * @brief Logs an info message to log file only.
 */
#define slog_info_f(fmt, ...)                                                  \
    _slog_log(LV_INFO, _slog_file,                                             \
              "\033[37m%s\033[0m \033[1;32m[INFO]\033[0m %s:%d -> " fmt "\n",  \
              _slog_get_time(), __FILE__, __LINE__, ##__VA_ARGS__)

/**
 * @brief Logs an error message to log file only.
 */
#define slog_error_f(fmt, ...)                                                 \
    _slog_log(LV_ERROR, _slog_file,                                            \
              "\033[37m%s\033[0m \033[1;31m[ERROR]\033[0m %s:%d -> " fmt "\n", \
              _slog_get_time(), __FILE__, __LINE__, ##__VA_ARGS__)

/**
 * @brief Logs an warn message to log file only.
 */
#define slog_warn_f(fmt, ...)                                                  \
    _slog_log(LV_WARN, _slog_file,                                             \
              "\033[37m%s\033[0m \033[1;33m[WARN]\033[0m %s:%d -> " fmt "\n",  \
              _slog_get_time(), __FILE__, __LINE__, ##__VA_ARGS__)

/**
 * @brief Logs an debug message to log file only.
 */
#define slog_debug_f(fmt, ...)                                                 \
    _slog_log(LV_DEBUG, _slog_file,                                            \
              "\033[37m%s\033[0m \033[1;34m[DEBUG]\033[0m %s:%d -> " fmt "\n", \
              _slog_get_time(), __FILE__, __LINE__, ##__VA_ARGS__)

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SLOG_H__
