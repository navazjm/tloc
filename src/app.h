#ifndef TLOC_APP_H
#define TLOC_APP_H

#include "summary.h"
#include <stddef.h>
#include <stdint.h>

typedef struct {
    const char* version;
    TLOC_File_Summary* file_summaries;
    uint16_t file_summaries_buffer_size;
    uint16_t file_summaries_count;

    char* path;
    uint8_t is_path_dir;
    uint8_t show_full_path;
    uint8_t include_untracked;
    uint8_t group_by_language;
    uint8_t exclude_unsupported;
} TLOC_App;

void tloc_app_init(TLOC_App* app);
void tloc_app_destroy(TLOC_App* app);
void tloc_app_parse_cmd_args(TLOC_App* app, int argc, char** argv);
void tloc_app_count_lines_of_code(TLOC_App* app);
void tloc_app_count_lines_of_code_file(TLOC_App* app, const char* file_path);
void tloc_app_count_lines_of_code_dir(TLOC_App* app);
void tloc_app_count_lines_of_code_dir_git(TLOC_App* app);
void tloc_app_count_lines_of_code_dir_recursion(TLOC_App* app, const char* dir_path);
void tloc_app_display_results(TLOC_App* app);
void tloc_app_display_results_by_file(TLOC_App* app);
void tloc_app_display_results_by_language(TLOC_App* app);

void tloc_print_usage_help(); // not really specific to the app ds, but dont really know where else to put this func dec

#endif
