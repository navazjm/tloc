#ifndef TLOC_APP_H
#define TLOC_APP_H

#include "options.h"
#include "summary.h"
#include <stddef.h>
#include <stdint.h>

typedef struct {
    const char* version;
    TLOC_Options opts;
    TLOC_File_Summaries file_summaries;
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

#endif
