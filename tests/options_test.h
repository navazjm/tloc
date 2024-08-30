#ifndef TLOC_OPTIONS_TEST_H
#define TLOC_OPTIONS_TEST_H
#include "munit.h"

MunitResult tloc_options_map_arg_test(const MunitParameter params[], void* data);

extern MunitTest tloc_options_tests[];
extern MunitSuite tloc_options_test_suite;

#endif
