#ifndef TLOC_LANGUAGE_TEST_H
#define TLOC_LANGUAGE_TEST_H
#include "munit.h"

MunitResult tloc_language_get_by_extension_test(const MunitParameter params[], void* data);

extern MunitTest tloc_language_tests[];
extern MunitSuite tloc_language_test_suite;

#endif
