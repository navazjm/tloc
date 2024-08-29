#ifndef TLOC_UTILS_H
#define TLOC_UTILS_H

#include "options.h"

void tloc_utils_split_cmd_arg(const char* input, char* tokens[2]);
char* tloc_utils_string_trim_whitespace(char* str);
bool tloc_utils_string_ends_with(const char* str, const char* suffix);
void tloc_utils_string_strip_prefix(char* str, const char* prefix);
void tloc_utils_format_file_path_by_pp_option(char* file_path, TLOC_PP_Option pp_opt);
void tloc_utils_normalize_file_path(char* file_path);

#endif
