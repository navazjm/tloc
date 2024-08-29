#include "language.h"
#include "munit.h"

static char* tloc_language_get_by_extension_test_ext_params[] = {"c", "md", "hpp", "txt", "NULL", NULL};
MunitParameterEnum tloc_language_get_by_extension_test_params[] = {
    {"ext", tloc_language_get_by_extension_test_ext_params},
    {NULL, NULL},
};
MunitResult tloc_language_get_by_extension_test(const MunitParameter params[], void* data) {
    (void)data;

    const char* ext = munit_parameters_get(params, "ext");
    const TLOC_Language* lang = tloc_language_get_by_extension(ext);
    if (strcmp(ext, "txt") == 0 || strcmp(ext, "NULL") == 0) {
        munit_assert_null(lang);
    } else if (strcmp(ext, "c") == 0) {
        munit_assert_not_null(lang);
        munit_assert_string_equal(lang->name, "C");
    } else if (strcmp(ext, "md") == 0) {
        munit_assert_not_null(lang);
        munit_assert_string_equal(lang->name, "Markdown");
    } else if (strcmp(ext, "hpp") == 0) {
        munit_assert_not_null(lang);
        munit_assert_string_equal(lang->name, "C/C++ Header");
    }
    return MUNIT_OK;
}

MunitTest tloc_language_tests[] = {{(char*)"/split_cmd_arg_test", tloc_language_get_by_extension_test, NULL, NULL,
                                    MUNIT_TEST_OPTION_NONE, tloc_language_get_by_extension_test_params},
                                   {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

MunitSuite tloc_language_test_suite = {(char*)"/utils", tloc_language_tests, NULL, 1, MUNIT_SUITE_OPTION_NONE};
