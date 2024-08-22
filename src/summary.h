#ifndef TLOC_SUMMARY_H
#define TLOC_SUMMARY_H

typedef struct {
    const char* name;
    const char* ext;
    int total_lines;
    int code_lines;
    int comment_lines;
    int blank_lines;
} TLOC_File_Summary;

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
