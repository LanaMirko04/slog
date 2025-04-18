# SLog Usage Examples
This directory contains simple examples demonstrating the usage of SLog.

## How to Run:
To compile and run an example, use the following commands:

```sh
$ gcc <example_name.c> -o <example_name> -lslog
$ ./<example_name> <args>
```

### Demo
To run the demo:

```sh
$ gcc demo.c -o demo -lslog
$ ./demo demo.log
```

### Console-only Logs
To compile and run the console-only logging example:

**Without debug logs**

```sh
$ gcc log_on_console.c -o log_on_console -lslog
$ ./log_on_console
```

**With debug log**

```
$ gcc log_on_console.c -o log_on_console -lslog -DDEBUG
$ ./log_on_console
```
### File-only Logs
To compile and run the file-only logging example:

**Without debug logs**

```sh
$ gcc log_on_file.c -o log_on_file -lslog
$ ./log_on_file file.log
```

**With debug log**

```
$ gcc log_on_file.c -o log_on_file -lslog -DDEBUG
$ ./log_on_file file.log
```

## Notes
If you have not installed the SLog library, specify the path to the library
using the -L option:

```sh
$ gcc <example_name.c> -o <example_name> -L/path/to/libslog.a -lslog
```
