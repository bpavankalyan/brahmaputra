#include <stdio.h>

#include <string.h>

#include "bmd_validate.h"

#include "../test/munit.h"

/* 
munit testing
how to run:-

gcc -Wall -I/usr/include/libxml2  -o hello  test_validate_bmd_munit.c bmd_validate.c ../extract_bmd/bmd_extract.c  -lxml2  `mysql_config --cflags --libs`  ${INCLUDE} ../test/munit.c


*/

static MunitResult
test_bmd_validate(const MunitParameter params[], void * fixture) {

  char * file = "bmd.xml";
  int x = validate_bmd(file);

  munit_assert_int(x, == , 1);

  return MUNIT_OK;
}

MunitTest test_suite_tests[] = {
  {
    (char * )
    "/example/bmd_validate",
    test_bmd_validate,
    NULL, NULL,
    MUNIT_TEST_OPTION_NONE,
    NULL
  },
  {
    NULL,
    NULL,
    NULL,
    NULL,
    MUNIT_TEST_OPTION_NONE,
    NULL
  }
};

static
const MunitSuite test_suite = {
  (char * )
  "",

  test_suite_tests,

  NULL,
  1,
  MUNIT_SUITE_OPTION_NONE
};

int main(int argc,
  const char * argv[]) {
  return munit_suite_main( & test_suite, NULL, argc, NULL);
}
