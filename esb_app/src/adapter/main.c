#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <curl/curl.h>
#include "adapter.h"



#if 0
int main()
{
    char * d1 = "998";
    char * s= "jdsdsk0";
    int d =998;
    char * s1="https://ifsc.razorpay.com/";
    char * s2= "HDFC0CAGSBK";
    char * file_name = (char *) call_function("APIURL", s1,s2);
    printf("%s\n", file_name);
    printf("\"Not Found\"\n");
    
    if((strcmp(file_name,"\"Not Found\"")!=0)){
    char * file =  call_function("insert_to_json_file",file_name,"http_test");
   // printf("%s\n", file);
    printf("%s\n", call_function("email", "Testmailchenab1@gmail.com",file));
  //  printf("%s\n", call_function("ftp", "test",file));

    //printf("%s\n", call_function("remove",file ,NULL));

    // xml_to_json("./xml2json/bmd.xml","./xml2json/output.json");
       




    }
    else 
    printf("null");
    
        free(file_name);
    return 0;
}
#endif


