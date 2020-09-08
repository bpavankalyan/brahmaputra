#include <stdio.h>

#include <string.h>

#include "bmd_extract.c"

#include "../test/munit.h"

/* 
munit testing
how to run:-
gcc -Wall -I/usr/include/libxml2  -o hello test_bmd.c   -lxml2 ${INCLUDE} ../test/munit.c

*/

static MunitResult
test_bmd_extract(const MunitParameter params[], void * fixture) {

  char * filename = "bmd.xml";
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

MunitTest test_suite_tests[] = {
  {
    (char * )
    "/example/bmd_extract",
    test_bmd_extract,
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

/*int main(){
  
  char * filename="bmd.xml";
  char * fields[10];
  extract_bmd(filename, fields); 
    
  printf("MessageID = %s\n",fields[0]);
  printf("MessageType = %s\n",fields[1]);
  printf("Sender = %s\n",fields[2]);
  printf("Destination = %s\n",fields[3]);
  printf("CreationDateTime = %s\n",fields[4]);
  printf("Signature = %s\n",fields[5]);
  printf("ReferenceID = %s\n",fields[6]);
  printf("Payload = %s\n",fields[7]);
  printf("UserProperties = %s\n",fields[8]);
  exit (0);  
}
*/
