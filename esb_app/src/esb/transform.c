#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <memory.h>

void apply_transform(char * transform_type, char * transport_key, char * transport_value, char * data_location,char* fields2[]) {
  /*char * fields[10];
  extract_bmd(data_location, fields); 
  char * payload = fields[7];*/
  char * payload = "HDFC0CAGSBK";
  char payload2[1000];
  strcpy(payload2,payload);
  if ((!strcmp(transform_type, ":IFSC_CODE")) && (!strcmp(transport_key, "API_URL"))) {
    printf("append payload to transport_value i.e. URL\n");
    
    for(int i=0;i<strlen(payload2);i++){	
        char ch = payload2[i];
	strncat(transport_value, &ch, 1);
    }

    fields2[0]=transport_value;
    //printf("%s\n",fields2[0]);

  } else if ((!strcmp(transform_type, "JSON")) && (!strcmp(transport_key, "SMTP"))) {
    printf("convert payload to json string\n");
    char* json="output.json";
    xml2json2(payload);
    printf("\n %s created\n", json);
    

  } else {
    printf("No transformation needed\n");


  }

}

