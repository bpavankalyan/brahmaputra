#include <stdio.h>
#include "bmd_extract.c"
#include <stdlib.h>
#include "/home/devika/Desktop/brahmaputra/esb_app/src/kd_xml/src/test/munit.h"
//#include "test/munit.h"
#include <libxml/parser.h>



static void *
parse_bmd_xml_setup(const MunitParameter params[], void *user_data)
{
 char * filename="bmd.xml";
  char * fields[20];
  //struct dk;
  dk *b =(dk*)malloc(sizeof(dk));
   b = extract_bmd(filename, fields);
  return b;
}



  dk *get_value(void)
{
  dk *abc = (dk *)malloc(sizeof(dk));
  abc->MessageID = "A9ECAEF2-107A-4452-9553-043B6D25386E";
  abc->MessageType = "CreditReport";
  abc->Sender = "756E2EAA-1D5B-4BC0-ACC4-4CEB669408DA";
  abc->Destination = "6393F82F-4687-433D-AA23-1966330381FE";
  abc->CreationDateTime = "2020-08-12T05:18:00+0000";
  abc->Signature = "63f5f61f7a79301f715433f8f3689390d1f5da4f855169023300491c00b8113c1";
  abc->ReferenceID = "INV-PROFILE-8897121";
  //bmd_file->envelop_data = ex;
  abc->Payload = "001-01-12341";

  return abc;
}
/* Test function */
static MunitResult
test_parse_bmd_xml(const MunitParameter params[], void *fixture)
{
   dk *test_bmd = (dk *)fixture;
  dk *expected_bmd = get_value();
  /* is_bmd_valid returns 1 if valid */
  munit_assert_string_equal(test_bmd->MessageID,
                             expected_bmd->MessageID);
  munit_assert_string_equal(test_bmd->MessageType,
                            expected_bmd->MessageType);
  munit_assert_string_equal(test_bmd->Sender,
                            expected_bmd->Sender);
  munit_assert_string_equal(test_bmd->Destination,
                             expected_bmd->Destination);
  //munit_assert_string_equal(test_bmd->envelop_data->MessageType,
    //                        expected_bmd->envelop_data->MessageType);
  munit_assert_string_equal(test_bmd->CreationDateTime,
                             expected_bmd->CreationDateTime);
  //munit_assert_string_equal(test_bmd->envelop_data->MessageID,
    //                         expected_bmd->envelop_data->MessageID);
  munit_assert_string_equal(test_bmd->Signature,
                             expected_bmd->Signature);
  munit_assert_string_equal(test_bmd->ReferenceID,
                             expected_bmd->ReferenceID);
  munit_assert_string_equal(test_bmd->Payload,expected_bmd->Payload);
  
  return MUNIT_OK;
}

static void
parse_bmd_xml_tear_down(void *fixture)
{
   dk* b = (dk *)fixture;

  /* free(b->MessageID);
   free(b->MessageType);
   free(b->Sender);
   free(b->Destination);
   free(b->CreationDateTime);
    free(b->Signature);
    free(b->ReferenceID);
    free(b->UserProperties);
    free(b->payload);*/
    free(b);

}
MunitTest bmd_tests[] = {
    {
        "/parse_bmd_xml_test",   /* name */
        test_parse_bmd_xml,      /* test function */
        parse_bmd_xml_setup,     /* setup function for the test */
        parse_bmd_xml_tear_down, /* tear_down */
        MUNIT_TEST_OPTION_NONE,  /* options */
        NULL                     /* parameters */
    },
     {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};
     static const MunitSuite suite = {
    "/bmd_tests",           /* name */
    bmd_tests,              /* tests */
    NULL,                   /* suites */
    1,                      /* iterations */
    MUNIT_SUITE_OPTION_NONE /* options */
};

/* Run the the test suite */
int main(int argc, const char *argv[])
{
  return munit_suite_main(&suite, NULL, argc, NULL);
}

