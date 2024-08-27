#include "utils_test.h"
#include "munit.h"
#include "utils.h"
#include <string.h>

static char* tloc_utils_split_cmd_arg_test_arg_params[] = {"--foo=bar", "--foo=", "--foo", NULL};
MunitParameterEnum tloc_utils_split_cmd_arg_test_params[] = {
    {"argv", tloc_utils_split_cmd_arg_test_arg_params},
    {NULL, NULL},
};
MunitResult tloc_utils_split_cmd_arg_test(const MunitParameter params[], void* data) {
    (void)data;

    char* option[2];
    const char* argv = munit_parameters_get(params, "argv");
    tloc_utils_split_cmd_arg(argv, option);
    munit_assert_not_null(option[0]);
    munit_assert_string_equal(option[0], "--foo");

    if (strcmp(argv, "--foo=bar") == 0) {
        munit_assert_string_equal(option[1], "bar");
    } else {
        munit_assert_null(option[1]);
    }

    return MUNIT_OK;
}

static char* tloc_utils_string_trim_whitespace_test_str_params[] = {"   test", "test   ", "  test  ", "test",
                                                                    "",        "   ",     NULL};
MunitParameterEnum tloc_utils_string_trim_whitespace_test_params[] = {
    {"str", tloc_utils_string_trim_whitespace_test_str_params},
    {NULL, NULL},
};
MunitResult tloc_utils_string_trim_whitespace_test(const MunitParameter params[], void* data) {
    (void)data;
    const char* str_param = munit_parameters_get(params, "str");
    char* str = strdup(str_param);
    char* str_trimmed = tloc_utils_string_trim_whitespace(str);

    if (strcmp(str, "") == 0 || strcmp(str, "   ") == 0) {
        munit_assert_string_equal(str_trimmed, "");
    } else {
        munit_assert_string_equal(str_trimmed, "test");
    }

    return MUNIT_OK;
}

static char* tloc_utils_string_ends_with_test_str_params[] = {"test*/", "test*/int a = 0;", "int a = 0;", "", NULL};
static char* tloc_utils_string_ends_with_test_suffix_params[] = {"*/", NULL};
MunitParameterEnum tloc_utils_string_ends_with_test_params[] = {
    {"str", tloc_utils_string_ends_with_test_str_params},
    {"suffix", tloc_utils_string_ends_with_test_suffix_params},
    {NULL, NULL},
};
MunitResult tloc_utils_string_ends_with_test(const MunitParameter params[], void* data) {
    (void)data;

    const char* str_param = munit_parameters_get(params, "str");
    const char* suffix_param = munit_parameters_get(params, "suffix");
    bool ends_with = tloc_utils_string_ends_with(str_param, suffix_param);

    if (strcmp(str_param, "test*/") == 0) {
        munit_assert_true(ends_with);
    } else {
        munit_assert_false(ends_with);
    }

    return MUNIT_OK;
}

static char* tloc_utils_string_strip_prefix_test_str_params[] = {"/tloc/src/main.c", "tloc/src/main.c", "", NULL};
static char* tloc_utils_string_strip_prefix_test_prefix_params[] = {"/tloc/", NULL};
MunitParameterEnum tloc_utils_string_strip_prefix_test_params[] = {
    {"str", tloc_utils_string_strip_prefix_test_str_params},
    {"prefix", tloc_utils_string_strip_prefix_test_prefix_params},
    {NULL, NULL},
};
MunitResult tloc_utils_string_strip_prefix_test(const MunitParameter params[], void* data) {
    (void)data;

    const char* str_param = munit_parameters_get(params, "str");
    char* str = strdup(str_param);
    const char* prefix_param = munit_parameters_get(params, "prefix");
    tloc_utils_string_strip_prefix(str, prefix_param);

    if (strcmp(str_param, "/tloc/src/main.c") == 0) {
        munit_assert_string_equal(str, "src/main.c");
    } else {
        munit_assert_string_equal(str, str_param);
    }

    return MUNIT_OK;
}

MunitResult tloc_utils_trim_path_by_pp_option_test(const MunitParameter params[], void* data) {
    (void)params;
    (void)data;
    return MUNIT_OK;
}

MunitTest tloc_utils_tests[] = {{(char*)"/split_cmd_arg_test", tloc_utils_split_cmd_arg_test, NULL, NULL,
                                 MUNIT_TEST_OPTION_NONE, tloc_utils_split_cmd_arg_test_params},
                                {(char*)"/string_trim_whitespace_test", tloc_utils_string_trim_whitespace_test, NULL,
                                 NULL, MUNIT_TEST_OPTION_NONE, tloc_utils_string_trim_whitespace_test_params},
                                {(char*)"/string_ends_with_test", tloc_utils_string_ends_with_test, NULL, NULL,
                                 MUNIT_TEST_OPTION_NONE, tloc_utils_string_ends_with_test_params},
                                {(char*)"/string_strip_prefix_test", tloc_utils_string_strip_prefix_test, NULL, NULL,
                                 MUNIT_TEST_OPTION_NONE, tloc_utils_string_strip_prefix_test_params},
                                {(char*)"/trim_path_by_pp_option_test", tloc_utils_trim_path_by_pp_option_test, NULL,
                                 NULL, MUNIT_TEST_OPTION_NONE, NULL},
                                {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

MunitSuite tloc_utils_test_suite = {(char*)"/utils", tloc_utils_tests, NULL, 1, MUNIT_SUITE_OPTION_NONE};
