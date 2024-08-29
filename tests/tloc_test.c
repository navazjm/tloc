#include "language_test.h"
#include "munit.h"
#include "utils_test.h"

int main(int argc, char* argv[]) {
    MunitSuite tloc_sub_suites[] = {
        tloc_language_test_suite, tloc_utils_test_suite, {NULL, NULL, NULL, 0, MUNIT_SUITE_OPTION_NONE}};

    const MunitSuite tloc_test_suite = {(char*)"/tloc", NULL, tloc_sub_suites, 1, MUNIT_SUITE_OPTION_NONE};
    return munit_suite_main(&tloc_test_suite, NULL, argc, argv);
}
