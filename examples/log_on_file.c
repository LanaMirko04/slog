#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>
#include <slog.h>

int main(int argc, char *argv[1]) {
    if (argc != 2) {
        puts("Usage: log_on_file [FILE]");
        return EXIT_FAILURE;
    }

#ifdef DEBUG
    slog_level_t lv = LV_DEBUG;
#else
    slog_level_t lv = LV_WARN;
#endif // DEBUG

    // Initialize SLog (add -DDEBUG to enable the debug prints).
    slog_init(lv);

    int ret = slog_open_file(argv[1]);
    if (ERR == ret) {
        slog_error_c("Unable to open the file: %s", strerror(errno));
        return EXIT_FAILURE;
    }

    // File-only logging examples.
    slog_info_f("Informationl message");
    slog_error_f("Error message");
    slog_warn_f("Warning message");
    slog_debug_f("Debug message");

    slog_close_file();

    slog_info("Printing '%s' content", argv[1]);

    FILE *fp = fopen(argv[1], "r");
    if (NULL == fp) {
        slog_error_c("Unable to open the file: %s", strerror(errno));
        return EXIT_FAILURE;
    }

    char *line = NULL;
    size_t linecap = 0;
    ssize_t linelen;
    while ((linelen = getline(&line, &linecap, fp)) > EOF) {
        printf("%s", line);
    }

    fclose(fp);

    return EXIT_SUCCESS;
}
