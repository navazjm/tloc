#include "utils.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

/*
 * Splits a command line argument into two tokens, the option name and value.
 * Input:  --path="./src/"
 * Output: ["--path", "./src/"]
 *
 * Input:  --include-gitignore
 * Output: ["--include-gitignore", NULL]
 *
 * @param input The input command line argument to split.
 * @param tokens An array of two strings where the split tokens will be stored.
 */
void tloc_utils_split_cmd_arg(const char* input, char* tokens[2]) {
    tokens[0] = tokens[1] = NULL;

    const char* equal_sign_pos = strchr(input, '=');
    // Only the name part is present
    if (equal_sign_pos == NULL) {
        tokens[0] = strdup(input);
        return;
    }

    // Split the input into two tokens. token[0] = name and token[1] = value
    size_t name_length = equal_sign_pos - input;
    tokens[0] = (char*)malloc(name_length + 1);
    strncpy(tokens[0], input, name_length);
    tokens[0][name_length] = '\0';

    // Allocate and copy the value part
    char* temp_value = strdup(equal_sign_pos + 1);
    tokens[1] = strlen(temp_value) != 0 ? temp_value : NULL;
}

/*
 * Trims all leading and trailing whitespace in a string.
 *
 * Input:  "   // this is a code comment    "
 * Output: "// this is a code comment"
 */
char* tloc_utils_string_trim_whitespace(char* str) {
    char* end;

    // Trim leading space
    while (isspace((unsigned char)*str))
        str++;

    // All spaces
    if (*str == 0) {
        return str;
    }

    // Trim trailing space
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end))
        end--;

    end[1] = '\0';

    return str;
}

/*
 * Checks if a string ends with substring
 *
 * Input:  "abba", "ba"
 * Output: 1
 *
 * Input:  "abca", "ba"
 * Output: 0
 *
 * We use it to determine if a line of source code ends with chars representing end of a multiline comment.
 */
bool tloc_utils_string_ends_with(const char* str, const char* suffix) {
    if (str == NULL || suffix == NULL) {
        return false;
    }

    size_t str_len = strlen(str);
    size_t suffix_len = strlen(suffix);

    if (suffix_len > str_len) {
        return false;
    }

    return strncmp(str + str_len - suffix_len, suffix, suffix_len) == 0;
}

/*
 * Strips prefix from string
 *
 * Input:  "example", "ex"
 * Output: "ample"
 */
void tloc_utils_string_strip_prefix(char* dest, const char* prefix) {
    if (dest == NULL || prefix == NULL) {
        return;
    }

    size_t dest_len = strlen(dest);
    size_t prefix_len = strlen(prefix);

    if (strncmp(dest, prefix, prefix_len) == 0) {
        memmove(dest, dest + prefix_len, dest_len - prefix_len + 1);
    }
}

/*
 * Helper function to format file path depending on TLOC_PP_Option
 * TLOC_PP_NONE: /Users/michael/repos/tloc/src/tloc.c -> tloc.c
 * TLOC_PP: /Users/michael/repos/tloc/src/tloc.c -> /src/tloc.c
 * TLOC_PP_S: /Users/michael/repos/tloc/src/tloc.c -> /s/tloc.c
 * TLOC_PP_A: /Users/michael/repos/tloc/src/tloc.c -> /Users/michael/repos/tloc/src/tloc.c
 * TLOC_PP_AS: /Users/michael/repos/tloc/src/tloc.c -> /U/m/r/t/s/tloc.c
 */
void tloc_utils_format_file_path_by_pp_option(char* file_path, TLOC_PP_Option pp_opt) {
    switch (pp_opt) {
        case TLOC_PP_NONE: { // trim file path to just filename.ext
            char* last_slash = strrchr(file_path, '/');
            if (last_slash) {
                // Move the string to point to the character after the last '/'
                memmove(file_path, last_slash + 1, strlen(last_slash));
            }
            break;
        }
        case TLOC_PP: { // trim file path to parent/filename.ext
            char* last_slash = strrchr(file_path, '/');
            if (last_slash) {
                *last_slash = '\0'; // Temporarily terminate the string before the last slash
                char* second_last_slash = strrchr(file_path, '/');
                *last_slash = '/'; // Restore the last slash
                if (second_last_slash) {
                    // move the string to start after the second-to-last '/'
                    memmove(file_path, second_last_slash, strlen(second_last_slash) + 1);
                }
            }
            break;
        }
        case TLOC_PP_S: { // trim file path to p/filename.ext, p being the first letter of parent dir
            char* last_slash = strrchr(file_path, '/');
            if (last_slash) {
                *last_slash = '\0'; // Temporarily terminate the string before the last slash
                char* second_last_slash = strrchr(file_path, '/');
                *last_slash = '/'; // Restore the last slash
                if (second_last_slash) {
                    // move the string to start after the second-to-last '/'
                    memmove(file_path, second_last_slash, strlen(second_last_slash));
                    memmove(file_path + 2, last_slash, strlen(last_slash));
                    file_path[strlen(last_slash) + 2] = '\0';
                }
            }
            break;
        }
        case TLOC_PP_A: {
            // Already stored the full file path in file_path, no modification needed
            break;
        }
        case TLOC_PP_AS: { // trim file path to only show the first letter of all directories
            char* p = file_path;
            char* next_slash;
            while ((next_slash = strchr(p, '/')) != NULL) {
                if (p != file_path) {
                    memmove(p + 1, next_slash, strlen(next_slash) + 1);
                    p += 2;
                } else {
                    p = next_slash + 1;
                }
            }
            break;
        }
    }
}

/*
 * Helper function to normalize file path names
 * ../tloc/src/tloc.c -> /tloc/src/tloc.c
 * ./tloc/src/tloc.c  -> /tloc/src/tloc.c
 * /tloc/src/tloc.c   -> /tloc/src/tloc.c
 * tloc/src/tloc.c    -> /tloc/src/tloc.c
 */
void tloc_utils_normalize_file_path(char* file_path) {
    size_t file_path_len = strlen(file_path);
    if (file_path[0] == '/') {
        return;
    }

    if (strncmp(file_path, "./", 2) == 0) {
        memmove(file_path, file_path + 1, file_path_len);
        return;
    }

    if (strncmp(file_path, "../", 3) == 0) {
        memmove(file_path, file_path + 2, file_path_len - 1);
        return;
    }

    memmove(file_path + 1, file_path, file_path_len + 1);
    file_path[0] = '/';
}
