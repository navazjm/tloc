#include "summary.h"
#include <stdlib.h>

bool tloc_summary_file_summaries_init(TLOC_File_Summaries* summaries, size_t initial_capacity) {
    summaries->items = (TLOC_File_Summary*)malloc(initial_capacity * sizeof(TLOC_File_Summary));
    if (summaries->items == NULL) {
        return true;
    }
    summaries->count = 0;
    summaries->capacity = initial_capacity;
    return false;
}

bool tloc_summary_file_summaries_append(TLOC_File_Summaries* summaries, TLOC_File_Summary* file_summary) {
    if (summaries->count == summaries->capacity) {
        summaries->capacity *= 2;
        summaries->items =
            (TLOC_File_Summary*)realloc(summaries->items, summaries->capacity * sizeof(TLOC_File_Summary));
        if (summaries->items == NULL) {
            return true;
        }
    }

    summaries->items[summaries->count++] = *file_summary;
    return false;
}

void tloc_summary_file_summaries_destroy(TLOC_File_Summaries* summaries) {
    if (summaries->items) {
        free(summaries->items);
    }
    summaries->count = 0;
    summaries->capacity = 0;
}

/* Iterate through language summary groups, returning a language summary based on supported language name.
 * If no language summary is find, we create a new one and return it
 */
TLOC_Language_Summary* tloc_summary_find_or_create_language_summary(TLOC_Language_Summary** groups, int* groups_count,
                                                                    const char* language_name) {
    for (int j = 0; j < *groups_count; j++) {
        if ((*groups)[j].name == language_name) {
            return &(*groups)[j];
        }
    }
    *groups = realloc(*groups, (*groups_count + 1) * sizeof(TLOC_Language_Summary));
    TLOC_Language_Summary* new_group = &(*groups)[(*groups_count)++];
    new_group->name = language_name;
    new_group->total_files = 0;
    new_group->total_lines = 0;
    new_group->blank_lines = 0;
    new_group->code_lines = 0;
    new_group->comment_lines = 0;

    return new_group;
}
