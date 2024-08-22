#include "language.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Adding a new language? Remember to update the Supported Language section in the
 * README. PRs will not be accepted until this requirement is fulfilled.
 */

// global list of supported langhuages
const TLOC_Language tloc_supported_languages[] = {
    {"C", "c", "//", "/*", "*/"},           {"C/C++ Header", "h, hpp", "//", "/*", "*/"},
    {"C++", "cpp", "//", "/*", "*/"},       {"Markdown", "md", NULL, "<!---", "-->"},
    {"JavaScript", "js", "//", "/*", "*/"}, {"TypeScript", "ts", "//", "/*", "*/"}};

/*
 * Returns a supported programming language based on file extension
 *
 * Input:  .md
 * Output: {"Markdown", "md", NULL, "<!---", "-->"}
 *
 * Input:  .txt
 * Output: NULL
 *
 * Input:  NULL
 * Output: NULL
 */
const TLOC_Language* tloc_language_get_by_extension(const char* extension) {
    if (extension == NULL) {
        return NULL;
    }

    size_t num_languages = sizeof(tloc_supported_languages) / sizeof(TLOC_Language);

    for (size_t i = 0; i < num_languages; i++) {
        char* token;
        char* extensions = strdup(tloc_supported_languages[i].extensions);
        token = strtok(extensions, ",");
        while (token != NULL) {
            if (strcmp(token, extension) == 0) {
                free(extensions);
                return &tloc_supported_languages[i];
            }
            token = strtok(NULL, ",");
        }
        free(extensions);
    }
    return NULL;
}

/* Iterate through tloc_supported_languages, displaying the language name and extensions */
void tloc_language_print_supported_languages() {
    size_t supported_languages_count = sizeof(tloc_supported_languages) / sizeof(TLOC_Language);
    size_t output_buffer_size = 3 + supported_languages_count * 64;
    char* output = (char*)malloc(output_buffer_size);
    if (output == NULL) {
        perror("Failed to allocate memory to print TLOC Supported Languages.\n");
        exit(EXIT_FAILURE);
    }
    output[0] = '\0';

    strcat(output, "----------------------------------\n");
    strcat(output, "Language             Extensions\n");
    strcat(output, "----------------------------------\n");

    char* output_line;

    for (size_t i = 0; i < supported_languages_count; i++) {
        asprintf(&output_line, "%-20s %-14s\n", tloc_supported_languages[i].name,
                 tloc_supported_languages[i].extensions);
        strcat(output, output_line);
    }

    printf("%s", output);
    free(output);
    free(output_line);
}
