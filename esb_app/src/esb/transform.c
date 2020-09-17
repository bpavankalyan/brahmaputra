#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <memory.h>

void apply_transform(char * transform_type, char * transport_key, char * transport_value, char * data_location,char* fields2[]) {

  if ((!strcmp(transform_type, ":IFSC_CODE")) && (!strcmp(transport_key, "API_URL"))) {
    printf("append payload to transport_value i.e. URL\n");
    //get payload from data_location
    //append and return it
    char * fields[10];
    extract_bmd(data_location, fields); 
    char * payload = fields[7];
 
    char * str3 = (char *) malloc(1 + strlen(transport_value)+ strlen(payload) );
    strcpy(str3, transport_value);
    strcat(str3, payload);
    printf("url : %s\n",str3);
    char* str4=str3;
    fields2[0]=str4;

  } else if ((!strcmp(transform_type, "JSON")) && (!strcmp(transport_key, "HTTP"))) {
    printf("convert payload to json string\n");
    printf("convert payload to json string\n");
    char* json="output.json";
    xml2json2(payload);
    printf("\n %s created\n", json);


  } else {
    printf("No transformation needed\n");


  }

}

