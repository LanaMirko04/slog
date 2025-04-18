# SLog API Documentation

**SLog** is a minimal C logging library with color-coded output, multiple
verbosity levels, and support for logging to both stdout and a file.

---

## Table of Contents
- [Data Types](#data-types)
- [Initialization](#initialization)
- [Log Macros](#log-macros)
    - [Dual Output (stdout + file)](#dual-output-stdout--file)
    - [Console Only](#console-only)
    - [File Only](#file-only)
- [Time Utilities](#time-utilities)

---

## Data Types

### `slog_level_t`
```c
typedef enum {
    LV_NONE     = 0x00,
    LV_INFO     = 0x01,
    LV_ERROR    = 0x02,
    LV_WARN     = 0x04,
    LV_DEBUG    = 0x08,
    LV_ALL      = 0x0F,
} slog_level_t;
```
Describes log verbosity levels.

---

## Initialization

### `void slog_init(uint8_t lv);`
Initializes the logging system with a chosen log level.

### `int slog_open_file(const char *filepath);`
Opens a file to log to. Returns `OK` or `ERR`.

### `void slog_close_file(void);`
Closes the currently open log file.

---

## Log Macros
Each log macro automatically prepends the current time, log level, source file,
and line number.

### Dual Output (stdout + file)
- `slog_info(fmt, ...)`
- `slog_error(fmt, ...)`
- `slog_warn(fmt, ...)`
- `slog_debug(fmt, ...)`

### Console Only
- `slog_info_c(fmt, ...)`
- `slog_error_c(fmt, ...)`
- `slog_warn_c(fmt, ...)`
- `slog_debug_c(fmt, ...)`

### File Only
- `slog_info_f(fmt, ...)`
- `slog_error_f(fmt, ...)`
- `slog_warn_f(fmt, ...)`
- `slog_debug_f(fmt, ...)`

Logs are formatted like that:
```
2025-04-18 15:00:00 [INFO] main.c:42 -> Message here
```
Colors used:
- **INFO**: bold green
- **ERROR**: bold red
- **WARN**: bold yellow
- **DEBUG**: bold blue
- Timestamps: light gray

---

## Return Codes
- `OK` = `0` (success)
- `ERR` = `-1` (failure)

---

## License
SLog is licensed under the [MIT](../LICENSE) License. Use at your own risk.
It’s called *SLog* for a reason.
