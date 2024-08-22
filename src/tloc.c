#include "app.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    TLOC_App* app = tloc_app_init();
    if (app == NULL) {
        fprintf(stderr, "Failed to initialize TLOC App\n");
        return EXIT_FAILURE;
    }

    tloc_app_parse_cmd_args(app, argc, argv);
    tloc_app_count_lines_of_code(app);
    tloc_app_display_results(app);
    tloc_app_destroy(&app);

    return EXIT_SUCCESS;
}
