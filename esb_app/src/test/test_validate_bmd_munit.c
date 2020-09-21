#include <stdio.h>
#include <string.h>
#include "../test/munit.h"

/* 
munit testing
how to run:-

gcc -Wall -I/usr/include/libxml2  -o hello  test_validate_bmd_munit.c bmd_validate.c ../extract_bmd/bmd_extract.c  -lxml2  `mysql_config --cflags --libs`  ${INCLUDE} ../test/munit.c
*/

/* Test function */
static MunitResult
test_bmd_validate1(const MunitParameter params[], void * fixture) {

  char * filename="Testcases_validate_bmd/bmd1.xml";
  char * fields[10];
  extract_bmd(filename, fields); 
  int x=validate_bmd(fields[1],fields[2],fields[3]);

  munit_assert_int(x ,== ,1);

  return MUNIT_OK;
}
/* Test function */
static MunitResult
test_bmd_validate2(const MunitParameter params[], void * fixture) {

  char * filename="Testcases_validate_bmd/bmd2.xml";
  char * fields[10];
  extract_bmd(filename, fields); 
  int x=validate_bmd(fields[1],fields[2],fields[3]);

  munit_assert_int(x ,== ,1);

  return MUNIT_OK;
}
/* Test function */
static MunitResult
test_bmd_validate3(const MunitParameter params[], void * fixture) {

  char * filename="Testcases_validate_bmd/bmd3.xml";
  char * fields[10];
  extract_bmd(filename, fields); 
  int x=validate_bmd(fields[1],fields[2],fields[3]);

  munit_assert_int(x ,== ,1);

  return MUNIT_OK;
}
/* Test function */
static MunitResult
test_bmd_validate4(const MunitParameter params[], void * fixture) {

  char * filename="Testcases_validate_bmd/bmd4.xml";
  char * fields[10];
  extract_bmd(filename, fields); 
  int x=validate_bmd(fields[1],fields[2],fields[3]);

  munit_assert_int(x ,== ,1);

  return MUNIT_OK;
}
/* Test function */
static MunitResult
test_bmd_validate5(const MunitParameter params[], void * fixture) {

  char * filename="Testcases_validate_bmd/bmd5.xml";
  char * fields[10];
  extract_bmd(filename, fields); 
  int x=validate_bmd(fields[1],fields[2],fields[3]);

  munit_assert_int(x ,== ,1);

  return MUNIT_OK;
}
/* Test function */
static MunitResult
test_bmd_validate6(const MunitParameter params[], void * fixture) {

  char * filename="Testcases_validate_bmd/bmd6.xml";
  char * fields[10];
  extract_bmd(filename, fields); 
  int x=validate_bmd(fields[1],fields[2],fields[3]);

  munit_assert_int(x ,== ,1);

  return MUNIT_OK;
}

/* Put all unit tests here. */
MunitTest test_suite_tests[] = {
  {
    (char * )
    "/example/bmd_validate1", /* name */
    test_bmd_validate1,       /* test function */
    NULL, NULL,
    MUNIT_TEST_OPTION_NONE,   /* options */
    NULL                      /* parameters */
  },
  {
    (char * )
    "/example/bmd_validate2",/*name */
    test_bmd_validate2,/*test function */
    NULL, NULL,
    MUNIT_TEST_OPTION_NONE,/* options */
    NULL /*parameters */
  },
  {
    (char * )
    "/example/bmd_validate3", /*name */
    test_bmd_validate3,/* test function */
    NULL, NULL,
    MUNIT_TEST_OPTION_NONE, /* options */
    NULL /* parameters */
  },
  {
    (char * ) 
    "/example/bmd_validate4", /* name */
    test_bmd_validate4,      /* test function */
    NULL, NULL,
    MUNIT_TEST_OPTION_NONE,  /* options */
    NULL                     /* parameters */
  },
  {
    (char * )
    "/example/bmd_validate5", /*name */
    test_bmd_validate5,        /* test function */
    NULL, NULL,                
    MUNIT_TEST_OPTION_NONE,    /* option */
    NULL                        /* parameters */
  },
  {
    (char * )
    "/example/bmd_validate6", /* name */
    test_bmd_validate6,       /* test function */
    NULL, NULL,        
    MUNIT_TEST_OPTION_NONE,   /* option */
    NULL                      /* parameters */
  },
   /* Mark the end of the array with an entry where the test
   * function is NULL */
  {
    NULL,
    NULL,
    NULL,
    NULL,
    MUNIT_TEST_OPTION_NONE,
    NULL
  }
};
/* Arrange the test cases into a test suite. */
static
const MunitSuite test_suite = {
  (char * )
  "",

  test_suite_tests,

  NULL,
  1,
  MUNIT_SUITE_OPTION_NONE
};

#if 0
/* Run the the test suite */
int main(int argc,
  const char * argv[]) {
  return munit_suite_main( & test_suite, NULL, argc, NULL);
}
#endif
