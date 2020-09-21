/**
 * @brief Contains:
 * 1.Extracting data from BMD
 * 2.Conversion from Xml to Json
 * 3.Declarations of XML(BMD) handling functions
 * 
 */

#include <stdio.h>
#ifndef BMD_H
#define BMD_H

struct map{
  char*  key;
  char* value;
};
typedef struct {
  char * MessageID;
  char * MessageType;
  char * Sender;
  char * Destination;
  char * CreationDateTime;
  char * Signature;
  char * ReferenceID;
  char* UserProperties;
}bmd_envelope;

typedef struct {
   
    bmd_envelope * envelope;
    char * Payload;
}bmd ;



bmd * extract_bmd (char * filename,  char* fields[]);
bmd * xml_to_json(char* xml_file, char* json_file);
int validate_bmd(char * MessageType, char* Sender, char* Destination);
void extract_bmd (char * filename,  char* fields[]);

#endif

