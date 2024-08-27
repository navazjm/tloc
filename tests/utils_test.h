#ifndef TLOC_UTILS_TEST_H
#define TLOC_UTILS_TEST_H
#include "munit.h"

MunitResult tloc_utils_split_cmd_arg_test(const MunitParameter params[], void* data);
MunitResult tloc_utils_string_trim_whitespace_test(const MunitParameter params[], void* data);
MunitResult tloc_utils_string_ends_with_test(const MunitParameter params[], void* data);
MunitResult tloc_utils_string_strip_prefix_test(const MunitParameter params[], void* data);
MunitResult tloc_utils_trim_path_by_pp_option_test(const MunitParameter params[], void* data);

extern MunitTest tloc_utils_tests[];
extern MunitSuite tloc_utils_test_suite;

#endif
