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

typedef struct 
{
    char  *MessageID;
    char  *MessageType;
    char  *Sender;
    char * Destination;
    char *CreationDateTime;
    char  *Signature;
    char  *ReferenceID;
}bmd_envelope;


typedef struct 
{
  bmd_envelope * envelope;
  char * payload;
} bmd;



bmd_envelope *  extract_envelope(char * filepath);
char * extract_payload(char * filepath);
int validate_xml_file (bmd * bmd_file);
bmd * parse_bmd_xml(char * filepath);
int is_bmd_valid(bmd* bd); 





#endif

