#include "summary.h"
#include <stdlib.h>

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
