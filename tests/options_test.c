#include "options_test.h"
#include "munit.h"
#include "options.h"
#include <string.h>

static char* tloc_options_map_arg_test_arg_params[] = {
    "-h", "-v", "-sl", "-g", "--language", "-eu", "-pp", "-pp-s", "-pp-a", "-pp-as", "--not-a-flag", "-naf", NULL};
MunitParameterEnum tloc_options_map_arg_test_params[] = {
    {"arg", tloc_options_map_arg_test_arg_params},
    {NULL, NULL},
};
MunitResult tloc_options_map_arg_test(const MunitParameter params[], void* data) {
    (void)data;

    // TODO: Add test for when we pass an arg_value to tloc_options_map_arg
    // Currently, valid args only used as flags

    const char* arg_flag = munit_parameters_get(params, "arg");
    TLOC_Options opts;
    if (strcmp(arg_flag, "-h") == 0 || strcmp(arg_flag, "-v") == 0 || strcmp(arg_flag, "-sl") == 0 ||
        strcmp(arg_flag, "-naf") == 0 || strcmp(arg_flag, "--not-a-flag") == 0) {
        bool found_valid_option = tloc_options_map_arg(&opts, arg_flag, NULL);
        munit_assert_false(found_valid_option);
    } else if (strcmp(arg_flag, "-g") == 0) {
        bool found_valid_option = tloc_options_map_arg(&opts, arg_flag, NULL);
        munit_assert_true(found_valid_option);
        munit_assert_true(opts.use_git);
    } else if (strcmp(arg_flag, "--language") == 0) {
        bool found_valid_option = tloc_options_map_arg(&opts, arg_flag, NULL);
        munit_assert_true(found_valid_option);
        munit_assert_true(opts.group_by_language);
    } else if (strcmp(arg_flag, "-eu") == 0) {
        bool found_valid_option = tloc_options_map_arg(&opts, arg_flag, NULL);
        munit_assert_true(found_valid_option);
        munit_assert_true(opts.exclude_unsupported);
    } else if (strcmp(arg_flag, "-pp") == 0) {
        bool found_valid_option = tloc_options_map_arg(&opts, arg_flag, NULL);
        munit_assert_true(found_valid_option);
        munit_assert_int(opts.print_parent, ==, TLOC_PP);
    } else if (strcmp(arg_flag, "-pp-s") == 0) {
        bool found_valid_option = tloc_options_map_arg(&opts, arg_flag, NULL);
        munit_assert_true(found_valid_option);
        munit_assert_int(opts.print_parent, ==, TLOC_PP_S);
    } else if (strcmp(arg_flag, "-pp-a") == 0) {
        bool found_valid_option = tloc_options_map_arg(&opts, arg_flag, NULL);
        munit_assert_true(found_valid_option);
        munit_assert_int(opts.print_parent, ==, TLOC_PP_A);
    } else if (strcmp(arg_flag, "-pp-as") == 0) {
        bool found_valid_option = tloc_options_map_arg(&opts, arg_flag, NULL);
        munit_assert_true(found_valid_option);
        munit_assert_int(opts.print_parent, ==, TLOC_PP_AS);
    }

    return MUNIT_OK;
}

MunitTest tloc_options_tests[] = {{(char*)"/split_cmd_arg_test", tloc_options_map_arg_test, NULL, NULL,
                                   MUNIT_TEST_OPTION_NONE, tloc_options_map_arg_test_params},
                                  {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

MunitSuite tloc_options_test_suite = {(char*)"/options", tloc_options_tests, NULL, 1, MUNIT_SUITE_OPTION_NONE};
