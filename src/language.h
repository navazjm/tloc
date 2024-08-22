#ifndef TLOC_LANGUAGE_H
#define TLOC_LANGUAGE_H

typedef struct {
    const char* name;
    const char* extensions;
    const char* singleline_comment;
    const char* multiline_comment_start;
    const char* multiline_comment_end;
} TLOC_Language;

extern const TLOC_Language tloc_supported_languages[];
const TLOC_Language* tloc_language_get_by_extension(const char* extension);

void tloc_language_print_supported_languages();

#endif
