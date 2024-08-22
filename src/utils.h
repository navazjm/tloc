#ifndef TLOC_UTILS_H
#define TLOC_UTILS_H

void tloc_utils_split_cmd_arg(const char* input, char* tokens[2]);
char* tloc_utils_string_trim_whitespace(char* str);
int tloc_utils_string_ends_with(const char* str, const char* suffix);
void tloc_utils_strip_path_from_name(char* str, const char* prefix);

#endif
