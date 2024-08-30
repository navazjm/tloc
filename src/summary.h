#ifndef TLOC_SUMMARY_H
#define TLOC_SUMMARY_H

#include <stdbool.h>
#include <stddef.h>

typedef struct {
    const char* name;
    const char* ext;
    int total_lines;
    int code_lines;
    int comment_lines;
    int blank_lines;
} TLOC_File_Summary;

typedef struct {
    TLOC_File_Summary* items;
    size_t count;
    size_t capacity;
} TLOC_File_Summaries;

bool tloc_summary_file_summaries_init(TLOC_File_Summaries* summaries, size_t initial_capacity);
bool tloc_summary_file_summaries_append(TLOC_File_Summaries* summaries, TLOC_File_Summary* file_summary);
void tloc_summary_file_summaries_destroy(TLOC_File_Summaries* summaries);

typedef struct {
    const char* name;
    int total_files;
    int total_lines;
    int code_lines;
    int comment_lines;
    int blank_lines;
} TLOC_Language_Summary;

TLOC_Language_Summary* tloc_summary_find_or_create_language_summary(TLOC_Language_Summary** groups, int* groups_count,
                                                                    const char* language_name);

#endif
