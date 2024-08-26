#ifndef TLOC_OPTIONS_H
#define TLOC_OPTIONS_H

#include <stdbool.h>
#include <stddef.h>

typedef struct {
    char* path;
    bool include_untracked;
    bool group_by_language;
    bool exclude_unsupported;
} TLOC_Options;

void tloc_options_init(TLOC_Options* opts);
void tloc_options_destory(TLOC_Options* opts);

static inline void tloc_options_set_include_untracked(TLOC_Options* opts) { opts->include_untracked = true; }
static inline void tloc_options_set_group_by_language(TLOC_Options* opts) { opts->group_by_language = true; }
static inline void tloc_options_set_exclude_unsupported(TLOC_Options* opts) { opts->exclude_unsupported = true; }

typedef void (*TLOC_Set_Option_Func)(TLOC_Options*);

typedef struct {
    const char* shorthand;
    const char* longhand;
    const char* description;
    TLOC_Set_Option_Func set_option;
} TLOC_Arg;

extern const TLOC_Arg tloc_args[];
extern const size_t tloc_args_count;
extern const size_t tloc_args_filtering_sorting_starting_idx;
extern const size_t tloc_args_displaying_starting_idx;

void tloc_options_map_arg(TLOC_Options* opts, const char* arg_name);
void tloc_options_args_print_help();

#endif
