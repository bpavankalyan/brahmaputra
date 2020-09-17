#include <stdio.h>

#include <string.h>

#include "bmd_extract.h"

#include "../test/munit.h"

/* 
munit testing
how to run:-
 gcc -Wall -I/usr/include/libxml2  -o hello test_bmd_munit.c bmd_extract.c  -lxml2 ${INCLUDE} ../test/munit.c

*/
/* Test function */
static MunitResult
test_bmd_extract(const MunitParameter params[], void * fixture) {

  char * filename = "bmd.xml";
  char * fields[20];
  extract_bmd(filename, fields); /*this is explained in extract_bmd/bmd_extract.c */
  char * MessageID = "A9ECAEF2-107A-4452-9553-043B6D25386E";
  char * MessageType = "CreditReport";
  char * Sender = "756E2EAA-1D5B-4BC0-ACC4-4CEB669408DA";
  char * Destination = "6393F82F-4687-433D-AA23-1966330381FE";
  char * CreationDateTime = "2020-08-12T05:18:00+0000";
  char * Signature = "63f5f61f7a79301f715433f8f3689390d1f5da4f855169023300491c00b8113c";
  char * ReferenceID = "INV-PROFILE-889712";
  char * Payload = "001-01-1234";

  munit_assert_string_equal(MessageID,
    fields[0]);
  munit_assert_string_equal(MessageType,
    fields[1]);
  munit_assert_string_equal(Sender,
    fields[2]);
  munit_assert_string_equal(Destination,
    fields[3]);
  munit_assert_string_equal(CreationDateTime,
    fields[4]);
  munit_assert_string_equal(Signature,
    fields[5]);
  munit_assert_string_equal(ReferenceID,
    fields[6]);
  munit_assert_string_equal(Payload, fields[7]);
  return MUNIT_OK;
  }
  /* Test function */
  static MunitResult
test_bmd_extract1(const MunitParameter params[], void * fixture) {
   
   
   char * filename = "Testcases_extract_bmd/bmd1.xml";
   char * fields[20];

  extract_bmd(filename, fields);
  char * MessageID = "A9ECAEF2";
  char * MessageType = "CreditReport";
  char * Sender = "756E2EAA";
  char * Destination = "6393F82F";
  char * CreationDateTime = "2020-08-12T05:18:00+0000";
  char * Signature = "63f5f61f";
  char * ReferenceID = "INV-PROFILE-889712";
  char * Payload = "001-01-1234";

  munit_assert_string_equal(MessageID,
    fields[0]);
  munit_assert_string_equal(MessageType,
    fields[1]);
  munit_assert_string_equal(Sender,
    fields[2]);
  munit_assert_string_equal(Destination,
    fields[3]);
  munit_assert_string_equal(CreationDateTime,
    fields[4]);
  munit_assert_string_equal(Signature,
    fields[5]);
  munit_assert_string_equal(ReferenceID,
    fields[6]);
  munit_assert_string_equal(Payload, fields[7]);

  return MUNIT_OK;
}
/* Test function */
static MunitResult
test_bmd_extract2(const MunitParameter params[], void * fixture) {
   
   
   char * filename = "Testcases_extract_bmd/bmd2.xml";
   char * fields[20];

  extract_bmd(filename, fields);
  char * MessageID = "55555EF2-107A-4452-9553-043B6D25PPPP";
  char * MessageType = "DebitCredit";
  char * Sender = "000E2EAA-1D5B-4BC0-ACC4-4C00069408DA";
  char * Destination = "0000F82F-4687-433D-AA23-1966330381FE";
  char * CreationDateTime = "2020-09-10T18:08:00+0000";
  char * Signature = "63f5f61f7a99991f715433f8f3689390d1f5da4f855169023300491c00b8113c";
  char * ReferenceID = "8NV-PROFILE-999712";
  char * Payload = "333-22-4444";

  munit_assert_string_equal(MessageID,
    fields[0]);
  munit_assert_string_equal(MessageType,
    fields[1]);
  munit_assert_string_equal(Sender,
    fields[2]);
  munit_assert_string_equal(Destination,
    fields[3]);
  munit_assert_string_equal(CreationDateTime,
    fields[4]);
  munit_assert_string_equal(Signature,
    fields[5]);
  munit_assert_string_equal(ReferenceID,
    fields[6]);
  munit_assert_string_equal(Payload, fields[7]);

  return MUNIT_OK;
}
/* Test function */
static MunitResult
test_bmd_extract3(const MunitParameter params[], void * fixture) {
   
   
   char * filename = "Testcases_extract_bmd/bmd3.xml";
   char * fields[20];

  extract_bmd(filename, fields);
  char * MessageID = "M3";
  char * MessageType = "Bal";
  char * Sender = "S3";
  char * Destination = "D3";
  char * CreationDateTime = "2020-08-12T05:18:00+00001";
  char * Signature = "S3";
  char * ReferenceID = "R3";
  char * Payload = "001-01-12347";

  munit_assert_string_equal(MessageID,
    fields[0]);
  munit_assert_string_equal(MessageType,
    fields[1]);
  munit_assert_string_equal(Sender,
    fields[2]);
  munit_assert_string_equal(Destination,
    fields[3]);
  munit_assert_string_equal(CreationDateTime,
    fields[4]);
  munit_assert_string_equal(Signature,
    fields[5]);
  munit_assert_string_equal(ReferenceID,
    fields[6]);
  munit_assert_string_equal(Payload, fields[7]);

  return MUNIT_OK;
}
/* Test function */
static MunitResult
test_bmd_extract4(const MunitParameter params[], void * fixture) {
   
   
   char * filename = "Testcases_extract_bmd/bmd4.xml";
   char * fields[20];

  extract_bmd(filename, fields);
  char * MessageID = "M4";
  char * MessageType = "Bal";
  char * Sender = "S4";
  char * Destination = "D4";
  char * CreationDateTime = "2020-08-12T05:18:00+00001";
  char * Signature = "S4";
  char * ReferenceID = "R4";
  char * Payload = "001-01-12347";

  munit_assert_string_equal(MessageID,
    fields[0]);
  munit_assert_string_equal(MessageType,
    fields[1]);
  munit_assert_string_equal(Sender,
    fields[2]);
  munit_assert_string_equal(Destination,
    fields[3]);
  munit_assert_string_equal(CreationDateTime,
    fields[4]);
  munit_assert_string_equal(Signature,
    fields[5]);
  munit_assert_string_equal(ReferenceID,
    fields[6]);
  munit_assert_string_equal(Payload, fields[7]);

  return MUNIT_OK;
}
/* Test function */
static MunitResult
test_bmd_extract5(const MunitParameter params[], void * fixture) {
   
   
   char * filename = "Testcases_extract_bmd/bmd5.xml";
   char * fields[20];

  extract_bmd(filename, fields);
  char * MessageID = "M5";
  char * MessageType = "Bal";
  char * Sender = "S5";
  char * Destination = "D5";
  char * CreationDateTime = "2020-08-12T05:18:00+00001";
  char * Signature = "S5";
  char * ReferenceID = "R5";
  char * Payload = "001-01-12347";

  munit_assert_string_equal(MessageID,
    fields[0]);
  munit_assert_string_equal(MessageType,
    fields[1]);
  munit_assert_string_equal(Sender,
    fields[2]);
  munit_assert_string_equal(Destination,
    fields[3]);
  munit_assert_string_equal(CreationDateTime,
    fields[4]);
  munit_assert_string_equal(Signature,
    fields[5]);
  munit_assert_string_equal(ReferenceID,
    fields[6]);
  munit_assert_string_equal(Payload, fields[7]);

  return MUNIT_OK;
}
/* Test function */
static MunitResult
test_bmd_extract6(const MunitParameter params[], void * fixture) {
   
   
   char * filename = "Testcases_extract_bmd/bmd6.xml";
   char * fields[20];

  extract_bmd(filename, fields);
  char * MessageID = "M6";
  char * MessageType = "Bal";
  char * Sender = "S";
  char * Destination = "D";
  char * CreationDateTime = "2020-08-12T05:18:00+00001";
  char * Signature = "S6";
  char * ReferenceID = "R6";
  char * Payload = "001-01-12347";

  munit_assert_string_equal(MessageID,
    fields[0]);
  munit_assert_string_equal(MessageType,
    fields[1]);
  munit_assert_string_equal(Sender,
    fields[2]);
  munit_assert_string_equal(Destination,
    fields[3]);
  munit_assert_string_equal(CreationDateTime,
    fields[4]);
  munit_assert_string_equal(Signature,
    fields[5]);
  munit_assert_string_equal(ReferenceID,
    fields[6]);
  munit_assert_string_equal(Payload, fields[7]);

  return MUNIT_OK;
}
/* Test function */
static MunitResult
test_bmd_extract7(const MunitParameter params[], void * fixture) {
   
   
   char * filename = "Testcases_extract_bmd/bmd7.xml";
   char * fields[20];

  extract_bmd(filename, fields);
  char * MessageID = "M5";
  char * MessageType = "Bal";
  char * Sender = "";
  char * Destination = "";
  char * CreationDateTime = "2020-08-12T05:18:00+00001";
  char * Signature = "S7";
  char * ReferenceID = "R7";
  char * Payload = "001-01-12347";

  munit_assert_string_equal(MessageID,
    fields[0]);
  munit_assert_string_equal(MessageType,
    fields[1]);
  munit_assert_string_equal(Sender,
    fields[2]);
  munit_assert_string_equal(Destination,
    fields[3]);
  munit_assert_string_equal(CreationDateTime,
    fields[4]);
  munit_assert_string_equal(Signature,
    fields[5]);
  munit_assert_string_equal(ReferenceID,
    fields[6]);
  munit_assert_string_equal(Payload, fields[7]);

  return MUNIT_OK;
}
/* Put all unit tests here. */
MunitTest test_suite_tests[] = {
  {
    (char * )
    "/example/bmd_extract",   /* name */
    test_bmd_extract,         /* test function */
    NULL, NULL,
    MUNIT_TEST_OPTION_NONE,  /* options */
    NULL                    /* parameters */
  },
  {
    (char * )
    "/example/bmd_extract1",/* name */
    test_bmd_extract1,/* test function */
    NULL, NULL,
    MUNIT_TEST_OPTION_NONE, /* options */
    NULL /* parameters */
  },
  {
    (char * )
    "/example/bmd_extract2",/* name */
    test_bmd_extract2,/* test function */
    NULL, NULL,
    MUNIT_TEST_OPTION_NONE,/* options */
    NULL /* parameters */
  },
  {
    (char * )
    "/example/bmd_extract3",
    test_bmd_extract3,
    NULL, NULL,
    MUNIT_TEST_OPTION_NONE,/* options */
    NULL /* parameters */
  },
  {
    (char * )
    "/example/bmd_extract4",
    test_bmd_extract4,
    NULL, NULL,
    MUNIT_TEST_OPTION_NONE,/* options */
    NULL /* parameters */
  },
  {
    (char * )
    "/example/bmd_extract5",
    test_bmd_extract5,
    NULL, NULL,
    MUNIT_TEST_OPTION_NONE,/* options */
    NULL /* parameters */
  },
  {
    (char * )
    "/example/bmd_extract6",
    test_bmd_extract6,
    NULL, NULL,
    MUNIT_TEST_OPTION_NONE,/* options */
    NULL /* parameters */
  },
  {
    (char * )
    "/example/bmd_extract7",
    test_bmd_extract7,
    NULL, NULL,
    MUNIT_TEST_OPTION_NONE,/* options */
    NULL /* parameters */
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
/* Run the the test suite */
int main(int argc,
  const char * argv[]) {
  return munit_suite_main( & test_suite, NULL, argc, NULL);
}
#include <stdio.h>

#include <string.h>

#include "bmd_extract.h"

#include "../test/munit.h"

/* 
munit testing
how to run:-
 gcc -Wall -I/usr/include/libxml2  -o hello test_bmd_munit.c bmd_extract.c  -lxml2 ${INCLUDE} ../test/munit.c

*/
/* Test function */
static MunitResult
test_bmd_extract(const MunitParameter params[], void * fixture) {

  char * filename = "Testcases_extract_bmd/bmd.xml";
  char * fields[20];
  extract_bmd(filename, fields);
  char * MessageID = "A9ECAEF2-107A-4452-9553-043B6D25386E";
  char * MessageType = "CreditReport";
  char * Sender = "756E2EAA-1D5B-4BC0-ACC4-4CEB669408DA";
  char * Destination = "6393F82F-4687-433D-AA23-1966330381FE";
  char * CreationDateTime = "2020-08-12T05:18:00+0000";
  char * Signature = "63f5f61f7a79301f715433f8f3689390d1f5da4f855169023300491c00b8113c";
  char * ReferenceID = "INV-PROFILE-889712";
  char * Payload = "001-01-1234";

  munit_assert_string_equal(MessageID,
    fields[0]);
  munit_assert_string_equal(MessageType,
    fields[1]);
  munit_assert_string_equal(Sender,
    fields[2]);
  munit_assert_string_equal(Destination,
    fields[3]);
  munit_assert_string_equal(CreationDateTime,
    fields[4]);
  munit_assert_string_equal(Signature,
    fields[5]);
  munit_assert_string_equal(ReferenceID,
    fields[6]);
  munit_assert_string_equal(Payload, fields[7]);
  return MUNIT_OK;
  }
  /* Test function */
  static MunitResult
test_bmd_extract1(const MunitParameter params[], void * fixture) {
   
   
   char * filename = "Testcases_extract_bmd/bmd1.xml";
   char * fields[20];

  extract_bmd(filename, fields);
  char * MessageID = "A9ECAEF2";
  char * MessageType = "CreditReport";
  char * Sender = "756E2EAA";
  char * Destination = "6393F82F";
  char * CreationDateTime = "2020-08-12T05:18:00+0000";
  char * Signature = "63f5f61f";
  char * ReferenceID = "INV-PROFILE-889712";
  char * Payload = "001-01-1234";

  munit_assert_string_equal(MessageID,
    fields[0]);
  munit_assert_string_equal(MessageType,
    fields[1]);
  munit_assert_string_equal(Sender,
    fields[2]);
  munit_assert_string_equal(Destination,
    fields[3]);
  munit_assert_string_equal(CreationDateTime,
    fields[4]);
  munit_assert_string_equal(Signature,
    fields[5]);
  munit_assert_string_equal(ReferenceID,
    fields[6]);
  munit_assert_string_equal(Payload, fields[7]);

  return MUNIT_OK;
}
/* Test function */
static MunitResult
test_bmd_extract2(const MunitParameter params[], void * fixture) {
   
   
   char * filename = "Testcases_extract_bmd/bmd2.xml";
   char * fields[20];

  extract_bmd(filename, fields);
  char * MessageID = "55555EF2-107A-4452-9553-043B6D25PPPP";
  char * MessageType = "DebitCredit";
  char * Sender = "000E2EAA-1D5B-4BC0-ACC4-4C00069408DA";
  char * Destination = "0000F82F-4687-433D-AA23-1966330381FE";
  char * CreationDateTime = "2020-09-10T18:08:00+0000";
  char * Signature = "63f5f61f7a99991f715433f8f3689390d1f5da4f855169023300491c00b8113c";
  char * ReferenceID = "8NV-PROFILE-999712";
  char * Payload = "333-22-4444";

  munit_assert_string_equal(MessageID,
    fields[0]);
  munit_assert_string_equal(MessageType,
    fields[1]);
  munit_assert_string_equal(Sender,
    fields[2]);
  munit_assert_string_equal(Destination,
    fields[3]);
  munit_assert_string_equal(CreationDateTime,
    fields[4]);
  munit_assert_string_equal(Signature,
    fields[5]);
  munit_assert_string_equal(ReferenceID,
    fields[6]);
  munit_assert_string_equal(Payload, fields[7]);

  return MUNIT_OK;
}
/* Test function */
static MunitResult
test_bmd_extract3(const MunitParameter params[], void * fixture) {
   
   
   char * filename = "Testcases_extract_bmd/bmd3.xml";
   char * fields[20];

  extract_bmd(filename, fields);
  char * MessageID = "M3";
  char * MessageType = "Bal";
  char * Sender = "S3";
  char * Destination = "D3";
  char * CreationDateTime = "2020-08-12T05:18:00+00001";
  char * Signature = "S3";
  char * ReferenceID = "R3";
  char * Payload = "001-01-12347";

  munit_assert_string_equal(MessageID,
    fields[0]);
  munit_assert_string_equal(MessageType,
    fields[1]);
  munit_assert_string_equal(Sender,
    fields[2]);
  munit_assert_string_equal(Destination,
    fields[3]);
  munit_assert_string_equal(CreationDateTime,
    fields[4]);
  munit_assert_string_equal(Signature,
    fields[5]);
  munit_assert_string_equal(ReferenceID,
    fields[6]);
  munit_assert_string_equal(Payload, fields[7]);

  return MUNIT_OK;
}
/* Test function */
static MunitResult
test_bmd_extract4(const MunitParameter params[], void * fixture) {
   
   
   char * filename = "Testcases_extract_bmd/bmd4.xml";
   char * fields[20];

  extract_bmd(filename, fields);
  char * MessageID = "M4";
  char * MessageType = "Bal";
  char * Sender = "S4";
  char * Destination = "D4";
  char * CreationDateTime = "2020-08-12T05:18:00+00001";
  char * Signature = "S4";
  char * ReferenceID = "R4";
  char * Payload = "001-01-12347";

  munit_assert_string_equal(MessageID,
    fields[0]);
  munit_assert_string_equal(MessageType,
    fields[1]);
  munit_assert_string_equal(Sender,
    fields[2]);
  munit_assert_string_equal(Destination,
    fields[3]);
  munit_assert_string_equal(CreationDateTime,
    fields[4]);
  munit_assert_string_equal(Signature,
    fields[5]);
  munit_assert_string_equal(ReferenceID,
    fields[6]);
  munit_assert_string_equal(Payload, fields[7]);

  return MUNIT_OK;
}
/* Test function */
static MunitResult
test_bmd_extract5(const MunitParameter params[], void * fixture) {
   
   
   char * filename = "Testcases_extract_bmd/bmd5.xml";
   char * fields[20];

  extract_bmd(filename, fields);
  char * MessageID = "M5";
  char * MessageType = "Bal";
  char * Sender = "S5";
  char * Destination = "D5";
  char * CreationDateTime = "2020-08-12T05:18:00+00001";
  char * Signature = "S5";
  char * ReferenceID = "R5";
  char * Payload = "001-01-12347";

  munit_assert_string_equal(MessageID,
    fields[0]);
  munit_assert_string_equal(MessageType,
    fields[1]);
  munit_assert_string_equal(Sender,
    fields[2]);
  munit_assert_string_equal(Destination,
    fields[3]);
  munit_assert_string_equal(CreationDateTime,
    fields[4]);
  munit_assert_string_equal(Signature,
    fields[5]);
  munit_assert_string_equal(ReferenceID,
    fields[6]);
  munit_assert_string_equal(Payload, fields[7]);

  return MUNIT_OK;
}
/* Test function */
static MunitResult
test_bmd_extract6(const MunitParameter params[], void * fixture) {
   
   
   char * filename = "Testcases_extract_bmd/bmd6.xml";
   char * fields[20];

  extract_bmd(filename, fields);
  char * MessageID = "M6";
  char * MessageType = "Bal";
  char * Sender = "S";
  char * Destination = "D";
  char * CreationDateTime = "2020-08-12T05:18:00+00001";
  char * Signature = "S6";
  char * ReferenceID = "R6";
  char * Payload = "001-01-12347";

  munit_assert_string_equal(MessageID,
    fields[0]);
  munit_assert_string_equal(MessageType,
    fields[1]);
  munit_assert_string_equal(Sender,
    fields[2]);
  munit_assert_string_equal(Destination,
    fields[3]);
  munit_assert_string_equal(CreationDateTime,
    fields[4]);
  munit_assert_string_equal(Signature,
    fields[5]);
  munit_assert_string_equal(ReferenceID,
    fields[6]);
  munit_assert_string_equal(Payload, fields[7]);

  return MUNIT_OK;
}
/* Test function */
static MunitResult
test_bmd_extract7(const MunitParameter params[], void * fixture) {
   
   
   char * filename = "Testcases_extract_bmd/bmd7.xml";
   char * fields[20];

  extract_bmd(filename, fields);
  char * MessageID = "M5";
  char * MessageType = "Bal";
  char * Sender = "";
  char * Destination = "";
  char * CreationDateTime = "2020-08-12T05:18:00+00001";
  char * Signature = "S7";
  char * ReferenceID = "R7";
  char * Payload = "001-01-12347";

  munit_assert_string_equal(MessageID,
    fields[0]);
  munit_assert_string_equal(MessageType,
    fields[1]);
  munit_assert_string_equal(Sender,
    fields[2]);
  munit_assert_string_equal(Destination,
    fields[3]);
  munit_assert_string_equal(CreationDateTime,
    fields[4]);
  munit_assert_string_equal(Signature,
    fields[5]);
  munit_assert_string_equal(ReferenceID,
    fields[6]);
  munit_assert_string_equal(Payload, fields[7]);

  return MUNIT_OK;
}
/* Put all unit tests here. */
MunitTest test_suite_tests[] = {
  {
    (char * )
    "/example/bmd_extract",   /* name */
    test_bmd_extract,         /* test function */
    NULL, NULL,
    MUNIT_TEST_OPTION_NONE,  /* options */
    NULL                    /* parameters */
  },
  {
    (char * )
    "/example/bmd_extract1",/* name */
    test_bmd_extract1,/* test function */
    NULL, NULL,
    MUNIT_TEST_OPTION_NONE, /* options */
    NULL /* parameters */
  },
  {
    (char * )
    "/example/bmd_extract2",/* name */
    test_bmd_extract2,/* test function */
    NULL, NULL,
    MUNIT_TEST_OPTION_NONE,/* options */
    NULL /* parameters */
  },
  {
    (char * )
    "/example/bmd_extract3",
    test_bmd_extract3,
    NULL, NULL,
    MUNIT_TEST_OPTION_NONE,/* options */
    NULL /* parameters */
  },
  {
    (char * )
    "/example/bmd_extract4",
    test_bmd_extract4,
    NULL, NULL,
    MUNIT_TEST_OPTION_NONE,/* options */
    NULL /* parameters */
  },
  {
    (char * )
    "/example/bmd_extract5",
    test_bmd_extract5,
    NULL, NULL,
    MUNIT_TEST_OPTION_NONE,/* options */
    NULL /* parameters */
  },
  {
    (char * )
    "/example/bmd_extract6",
    test_bmd_extract6,
    NULL, NULL,
    MUNIT_TEST_OPTION_NONE,/* options */
    NULL /* parameters */
  },
  {
    (char * )
    "/example/bmd_extract7",
    test_bmd_extract7,
    NULL, NULL,
    MUNIT_TEST_OPTION_NONE,/* options */
    NULL /* parameters */
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
/* Run the the test suite */
int main(int argc,
  const char * argv[]) {
  return munit_suite_main( & test_suite, NULL, argc, NULL);
}
