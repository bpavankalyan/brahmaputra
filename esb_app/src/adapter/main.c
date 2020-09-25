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
    char * s1="https://v6.exchangerate-api.com/v6/bf946167a92147f08f8a1b9c/latest/";
    char * s2= "INR";
    char * file_name = (char *) call_function("APIURL", s1,s2);
    printf("%s\n", file_name);
    char * file =  call_function("insert_to_json_file",file_name,s2);
    printf("%s\n", file);
    printf("%s\n", call_function("email", "Testmailchenab1@gmail.com",file));
    printf("%s\n", call_function("ftp", "test",file));

    printf("%s\n", call_function("remove",file ,NULL));

    //remove(file);
    free(file_name);
    return 0;
}
#endif


