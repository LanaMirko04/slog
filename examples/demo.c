#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <slog.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        puts("Usage: demo [FILE]");
        return EXIT_FAILURE;
    }

    slog_init(LV_ALL);

    slog_info_c("Opening '%s' as log file", argv[1]);
    int ret = slog_open_file(argv[1]);
    if (ERR == ret) {
        slog_error_c("Unable to open the file: %s", strerror(errno));
        return EXIT_FAILURE;
    }
    slog_info_c("File opened correctly!");

    slog_info("Informational message on both 'stdout' and '%s'", argv[1]);
    sleep(1);
    slog_warn("Warning message on both 'stdout' and '%s'", argv[1]);
    sleep(1);
    slog_debug("Debugging message on both 'stdout' and '%s'", argv[1]);
    sleep(1);
    slog_error("Error message on both 'stdout' and '%s'", argv[1]);
    sleep(1);

    slog_info_f("Exiting demo...");
    slog_info_c("Closing '%s'", argv[1]);
    slog_close_file();

    return EXIT_SUCCESS;
}
