# Shitty Logging (SLog)

**Shitty Logging** (SLog) is an easy-to-use logging library for C programming language. It provides a basic logging functionality with different log levels: *INFO*, *DEBUG*, *WARNING* and *ERROR*.

## Features

- Logging messages with different log levels.
- Customizable log output.
- Color support.

## Installation

```shell
$ git clone https://github.com/LanaMirko04/slog.git
$ cd slog
$ sudo make install
```

or

Copy files in src directory to your project

## Usage
#### Console logging
```c
#include <stdio.h>
#include <slog.h>

int main(int argc, char *argv[]) {
  SLOG_INFO("This is an info message");
  SLOG_DEBUG("This is a debug message");
  SLOG_WARNING("This is a warning message");
  SLOG_ERROR("This is an error message");

  return 0;
}
```

#### File logging
```c
#include <stdio.h>
#include <slog.h>

int main(int argc, char *argv[]) {
  SLOG_USE_FILE();

  SLOG_INFO("This is an info message");
  SLOG_DEBUG("This is a debug message");
  SLOG_WARNING("This is a warning message");
  SLOG_ERROR("This is an error message");

  return 0;
}
```

#### Compilation
```shell
gcc -o example example.c -lslog
```
If you need debug logs
```shell
gcc -o example example.c -D_SLOG_DEBUG -lslog
```

## License
SLog is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.
