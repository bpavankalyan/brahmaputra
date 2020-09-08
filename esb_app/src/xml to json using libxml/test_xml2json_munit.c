#include <stdio.h>
#include "../test/munit.h"
#include "xml2json.c"


/* 
munit testing
how to run:-
 gcc -Wall -I/usr/include/libxml2  -o hello test_xml2json_munit.c   -lxml2 ${INCLUDE} ../test/munit.c
*/

char *get_str_data(char *file)
{
  long f_size;
  char *str_data;
  size_t file_size, result;
  FILE *fp = fopen(file, "r");
  fseek(fp, 0, SEEK_END);
  /* Reads the size of the file */
  f_size = ftell(fp);
  fseek(fp, 0, SEEK_SET);
  file_size = sizeof(char) * f_size;
  str_data = malloc(file_size);
  /* fread returns number of items actually read. */
  result = fread(str_data, 1, f_size, fp);
  fclose(fp);
  return strdup(str_data);
}

/* Test setup function */
static void *
xml_to_json_setup(const MunitParameter params[], void *user_data)
{
  char * xml_file  = "bmd.xml";
  char * json_file ="bmd.json";
  xml_to_json(xml_file, json_file);
  char *json_data = get_str_data(json_file);
  return strdup(json_data);
}

/* Test function */
static MunitResult
test_xml_to_json(const MunitParameter params[], void *fixture)
{
  char *json_data = (char *)fixture;

  char *test_data = get_str_data("bmd2.json");

  munit_assert_string_equal(json_data, test_data);
  return MUNIT_OK;
}

static void
xml_to_json_tear_down(void *fixture)
{

  free(fixture);
}


/* Put all unit tests here. */
MunitTest bmd_tests[] = {
   
    {
        "/xml_to_json_test",    /* name */
        test_xml_to_json,       /* test function */
        xml_to_json_setup,      /* setup function for the test */
        xml_to_json_tear_down,  /* tear_down */
        MUNIT_TEST_OPTION_NONE, /* options */
        NULL                    /* parameters */
    },
    
    /* Mark the end of the array with an entry where the test
   * function is NULL */
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

/* Arrange the test cases into a test suite. */
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
