#include "options.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* Initialize base application options with sane defaults */
bool tloc_options_init(TLOC_Options* opts) {
    opts->path = getcwd(NULL, 0);
    if (opts->path == NULL) {
        return true;
    }
    opts->use_git = false;
    opts->group_by_language = false;
    opts->exclude_unsupported = false;
    opts->print_parent = TLOC_PP_NONE;
    return false;
}

/* Free allocated memory for options struct */
void tloc_options_destroy(TLOC_Options* opts) {
    if (opts->path) {
        free(opts->path);
    }
}

/* Dev Helper: Display all opts names and values */
void tloc_options_print(TLOC_Options* opts) {
    printf("opts->path: %s\n", opts->path);
    printf("opts->use_git: %s\n", opts->use_git ? "True" : "False");
    printf("opts->group_by_language: %s\n", opts->group_by_language ? "True" : "False");
    printf("opts->exclude_unsupported: %s\n", opts->exclude_unsupported ? "True" : "False");
    switch (opts->print_parent) {
        case TLOC_PP_NONE:
            printf("opts->print_parent: NONE\n");
            break;
        case TLOC_PP:
            printf("opts->print_parent: PP\n");
            break;
        case TLOC_PP_S:
            printf("opts->print_parent: PP-S\n");
            break;
        case TLOC_PP_A:
            printf("opts->print_parent: PP-A\n");
            break;
        case TLOC_PP_AS:
            printf("opts->print_parent: PP-AS\n");
            break;
    }
}

/* Global list of valid command line args */
const TLOC_Arg tloc_args[] = {
    // META OPTIONS
    {"-h", "--help", "Display list of command-line options.", NULL},
    {"-v", "--version", "Display installed version of tloc.", NULL},
    {"-sl", "--supported-languages", "Display a list of supported programming languages.", NULL},
    // FILTERING AND SORTING OPTIONS
    {"-g", "--git", "Only include files being tracked by Git.", tloc_options_set_use_git},
    // DISPLAYING OPTIONS
    {"-l", "--language", "List data by programming languages, not by files.", tloc_options_set_group_by_language},
    {"-eu", "--exclude-unsupported", "Exclude unsupported file types/langauges from being displayed.",
     tloc_options_set_exclude_unsupported},
    {"-pp", "--print-parent", "Print file name as parent/filename.", tloc_options_set_print_parent},
    {"-pp-s", "--print-parent-short", "Print file name as p/filename.", tloc_options_set_print_parent_short},
    {"-pp-a", "--print-parent-all", "Print file name including all parent dirs relative to provided path.",
     tloc_options_set_print_parent_all},
    {"-pp-as", "--print-parent-all-short",
     "Print file name including only first letter for all parent dirs relative to provided path.",
     tloc_options_set_print_parent_all_short},
};
/* track size of tloc args array */
const size_t tloc_args_count = sizeof(tloc_args) / sizeof(TLOC_Arg);

/* track where filter and sorting options begin */
const size_t tloc_args_filtering_sorting_starting_idx = 3;
/* track where displaying options begin */
const size_t tloc_args_displaying_starting_idx = 4;

/*
 * Map command line arg flags to respective option property
 *
 * @returns true/false if valid option was found
 * */
bool tloc_options_map_arg(TLOC_Options* opts, const char* arg_flag, const void* arg_value) {
    for (size_t i = tloc_args_filtering_sorting_starting_idx; i < tloc_args_count; i++) {
        TLOC_Arg arg = tloc_args[i];

        if (strcmp(arg_flag, arg.shorthand) == 0 || strcmp(arg_flag, arg.longhand) == 0) {
            if (arg_value) {
                arg.set_option_func(opts, arg_value);
            } else {
                arg.set_option_func(opts, (const void*)(intptr_t) true);
            }
            return true;
        }
    }

    return false;
}

/* Print the usage help options */
void tloc_options_args_print_help() {
    size_t buffer_size = 1024 + tloc_args_count * 48;
    char* output = (char*)malloc(buffer_size);
    if (output == NULL) {
        perror("Failed to allocate memory");
        return;
    }
    output[0] = '\0';
    strcat(output, "USAGE: \n    tloc optional/path/ [options] \n\n"
                   "OPTIONAL FILE PATH:\n\n"
                   "* Can be a path to a directory or a specific file\n"
                   "* Will default to CWD, if one of the following conditions is met:\n"
                   "    1. Omitted\n"
                   "    2. Path does not exist\n"
                   "    3. Do not have read access permisions\n"
                   "    4. Not provided as the second command-line arg.\n\n"
                   "META OPTIONS:\n");

    char* output_line;
    for (size_t i = 0; i < tloc_args_count; i++) {
        if (i == tloc_args_filtering_sorting_starting_idx) {
            strcat(output, "\nFILTERING AND SORTING OPTIONS:\n");
        } else if (i == tloc_args_displaying_starting_idx) {
            strcat(output, "\nDISPLAYING OPTIONS:\n");
        }
        TLOC_Arg arg = arg = tloc_args[i];
        char* arg_flag;
        asprintf(&arg_flag, "    %s, %s", arg.shorthand, arg.longhand);

        asprintf(&output_line, "%-40s %s\n", arg_flag, arg.description);
        strcat(output, output_line);
        free(output_line);
        free(arg_flag);
    }

    strcat(output, "\nFor more details, please visit: https://github.com/navazjm/tloc/blob/main/docs/options.md\n");

    printf("%s", output);
    free(output);
}
