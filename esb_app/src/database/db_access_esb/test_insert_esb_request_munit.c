#include <stdio.h>
#include "insert_esb_request.h"

#include "../test/munit.h"

/* 
munit testing
how to run:-

gcc -Wall -I/usr/include/libxml2  -o hello  test_insert_esb_request_munit.c insert_esb_request.c ../extract_bmd/bmd_extract.c  -lxml2  `mysql_config --cflags --libs`    ${INCLUDE} ../test/munit.c


*/

static MunitResult
test_bmd_validate(const MunitParameter params[], void * fixture) {

  char * filename="bmd.xml";
  char * fields[10];
  extract_bmd(filename, fields); 
  int x=insert_esb_request(fields);
  munit_assert_int(x,==,1);

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


