#include <stdio.h>
#include "munit.h"
#include "stdlib.h"
//#include "munit.c"
#include "../adapter/adapter.h"


/* This is just to disable an MSVC warning about conditional
 * expressions being constant, which you shouldn't have to do for your
 * code.  It's only here because we want to be able to do silly things
 * like assert that 0 != 1 for our demo. */
#if defined(_MSC_VER)
#pragma warning(disable: 4127)
#endif


char * get_file_data(char * file_name)
{
    /* declare a file pointer */
FILE    *infile;
char    *buffer;
long    numbytes;
 
/* open an existing file for reading */
infile = fopen(file_name, "r");
 
/* quit if the file does not exist */
if(infile == NULL)
    return NULL;
 
/* Get the number of bytes */
fseek(infile, 0L, SEEK_END);
numbytes = ftell(infile);
 
/* reset the file position indicator to 
the beginning of the file */
fseek(infile, 0L, SEEK_SET);	
 
/* grab sufficient memory for the 
buffer to hold the text */
buffer = (char*)calloc(numbytes, sizeof(char));	
 
/* memory error */
if(buffer == NULL)
    return NULL;
 
/* copy all the text into the buffer */
fread(buffer, sizeof(char), numbytes, infile);
fclose(infile);
 
/* confirm we have read the file by
outputing it to the console */
 
/* free the memory we used for the buffer */
 return strdup(buffer);

}


static MunitResult test_email (const MunitParameter params[], void * fixture)
{
  char * output = (char *) call_function("email_send","Testmailchenab1@gmail.com","http.c");
  munit_assert_string_equal(output,"NO");
  output = (char *) call_function("email","Testmailchenab1@gmail.com","adapter.h");
  munit_assert_string_equal(output,"NO");

}



static MunitResult test_http_request (const MunitParameter params[], void * fixture)
{
  char * output = (char *) call_function("APIURL","https://ifsc.razorpay.com/","HDFC0CAGSBK");
  munit_assert_ptr_not_null(output);
 
}


/* Creating a test suite is pretty simple.  First, you'll need an
 * array of tests: */
static MunitTest test_suite_tests[] = {
  
  { (char*) "/example/xml_values", test_email, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  { (char*) "/example/bmd_valid", test_http_request, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  //{ (char*) "/example/bmd-validation", test_ftp, NULL, NULL, MUNIT_TEST_OPTION_NONE, test_params },


  { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};



/* Now we'll actually declare the test suite.  You could do this in
 * the main function, or on the heap, or whatever you want. */
static const MunitSuite test_suite = {
  /* This string will be prepended to all test names in this suite;
   * for example, "/example/rand" will become "/µnit/example/rand".
   * Note that, while it doesn't really matter for the top-level
   * suite, NULL signal the end of an array of tests; you should use
   * an empty string ("") instead. */
  (char*) "",
  /* The first parameter is the array of test suites. */
  test_suite_tests,
  /* In addition to containing test cases, suites can contain other
   * test suites.  This isn't necessary in this example, but it can be
   * a great help to projects with lots of tests by making it easier
   * to spread the tests across many files.  This is where you would
   * put "other_suites" (which is commented out above). */
  NULL,
  /* An interesting feature of µnit is that it supports automatically
   * running multiple iterations of the tests.  This is usually only
   * interesting if you make use of the PRNG to randomize your tests
   * cases a bit, or if you are doing performance testing and want to
   * average multiple runs.  0 is an alias for 1. */
  1,
  /* Just like MUNIT_TEST_OPTION_NONE, you can provide
   * MUNIT_SUITE_OPTION_NONE or 0 to use the default settings. */
  MUNIT_SUITE_OPTION_NONE
};

/* This is only necessary for EXIT_SUCCESS and EXIT_FAILURE, which you
 * *should* be using but probably aren't (no, zero and non-zero don't
 * always mean success and failure).  I guess my point is that nothing
 * about µnit requires it. */
#include <stdlib.h>
#if 1
int main(int argc, char** argv) {
  /* Finally, we'll actually run our test suite!  That second argument
   * is the user_data parameter which will be passed either to the
   * test or (if provided) the fixture setup function. */
  return munit_suite_main(&test_suite, NULL, argc, NULL);
}
#endif
