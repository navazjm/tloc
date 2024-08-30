#ifndef TLOC_OPTIONS_H
#define TLOC_OPTIONS_H

#include <stdbool.h>
#include <stddef.h>

typedef enum { TLOC_PP_NONE, TLOC_PP, TLOC_PP_S, TLOC_PP_A, TLOC_PP_AS } TLOC_PP_Option;

typedef struct {
    char* path;
    bool include_untracked;
    bool group_by_language;
    bool exclude_unsupported;
    TLOC_PP_Option print_parent;
} TLOC_Options;

void tloc_options_init(TLOC_Options* opts);
void tloc_options_destory(TLOC_Options* opts);
void tloc_options_print(TLOC_Options* opts);

static inline void tloc_options_set_include_untracked(TLOC_Options* opts, const void* value) {
    opts->include_untracked = value;
}
static inline void tloc_options_set_group_by_language(TLOC_Options* opts, const void* value) {
    opts->group_by_language = value;
}
static inline void tloc_options_set_exclude_unsupported(TLOC_Options* opts, const void* value) {
    opts->exclude_unsupported = value;
}
static inline void tloc_options_set_print_parent(TLOC_Options* opts, const void* value) {
    (void)value;
    opts->print_parent = TLOC_PP;
}
static inline void tloc_options_set_print_parent_short(TLOC_Options* opts, const void* value) {
    (void)value;
    opts->print_parent = TLOC_PP_S;
}
static inline void tloc_options_set_print_parent_all(TLOC_Options* opts, const void* value) {
    (void)value;
    opts->print_parent = TLOC_PP_A;
}
static inline void tloc_options_set_print_parent_all_short(TLOC_Options* opts, const void* value) {
    (void)value;
    opts->print_parent = TLOC_PP_AS;
}

typedef void (*TLOC_Set_Option_Func)(TLOC_Options*, const void*);

typedef struct {
    const char* shorthand;
    const char* longhand;
    const char* description;
    TLOC_Set_Option_Func set_option_func;
} TLOC_Arg;

extern const TLOC_Arg tloc_args[];
extern const size_t tloc_args_count;
extern const size_t tloc_args_filtering_sorting_starting_idx;
extern const size_t tloc_args_displaying_starting_idx;

bool tloc_options_map_arg(TLOC_Options* opts, const char* arg_flag, const void* arg_value);
void tloc_options_args_print_help();

#endif
