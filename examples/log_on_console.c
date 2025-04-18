#include <stdlib.h>
#include <slog.h>

int main(void) {
#ifdef DEBUG
    uint8_t lv = LV_ALL;
#else
    uint8_t lv = LV_ALL ^ LV_DEBUG;
#endif // DEBUG

    // Initialize SLog (add -DDEBUG to enable the debug prints).
    slog_init(lv);
    
    // Console-only logging examples.
    slog_info_c("Informationl message");
    slog_error_c("Error message");
    slog_warn_c("Warning message");
    slog_debug_c("Debug message");

    return EXIT_SUCCESS;
}
