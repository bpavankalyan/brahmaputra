/*
gcc -Wall -I/usr/include/libxml2  -o hello  test_insert_esb_request.c insert_esb_request.c ../extract_bmd/bmd_extract.c  -lxml2  `mysql_config --cflags --libs` 

The data extracted from the BMD envelope element is inserted as a row in the esb_request table. The status column's value for the newly inserted row should be RECEIVED 

*/

#include <stdio.h>
#include "insert_esb_request.h"


#if 0
int main(){
   char * filename="bmd.xml";
   char * fields[10];
   extract_bmd(filename, fields); 
   int x=insert_esb_request(fields);
   return 0;


}
#endif