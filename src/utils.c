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
    tokens[1] = strdup(equal_sign_pos + 1);
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
int tloc_utils_string_ends_with(const char* str, const char* suffix) {
    if (str == NULL || suffix == NULL) {
        return 0;
    }

    size_t str_len = strlen(str);
    size_t suffix_len = strlen(suffix);

    if (suffix_len > str_len) {
        return 0;
    }

    return strncmp(str + str_len - suffix_len, suffix, suffix_len) == 0;
}

/*
 * Strips root path name from the file name and replaces it with a '.'
 *
 * Input:  "/tloc/src/main.c", "/tloc/src"
 * Output: "./main.c"
 */
void tloc_utils_strip_path_from_name(char* file_name, const char* path_name) {
    size_t path_name_len = strlen(path_name);
    size_t file_name_len = strlen(file_name);

    if (strncmp(file_name, path_name, path_name_len) == 0) {
        memmove(file_name + 1, file_name + path_name_len, file_name_len - path_name_len + 1);
        file_name[0] = '.';
    }
}
