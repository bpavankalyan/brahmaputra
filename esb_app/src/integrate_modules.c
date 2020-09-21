/*
gcc -Wall -I/usr/include/libxml2  -o hello  integrate_modules.c    
validate_bmd/bmd_validate.c extract_bmd/bmd_extract.c  xml_to_json_using_libxml/xml2json.c  -lxml2  `mysql_config --cflags --libs`
*/

#include "../src/adapter/xml2json.h"
#include "../src/validate_bmd/bmd_validate.h"


#if 0
int main(){

//extract bmd file
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
//validate it
  int r=validate_bmd(filename);

  if(r==1){
//convert to json file
    char * output="bmd_generated.json";
    xml_to_json(filename, output); 
    printf("Done\n");
  }
  else printf("invalid bmd\n");
   return 0;
}
#endif