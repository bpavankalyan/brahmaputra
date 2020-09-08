#include <stdio.h>

#include <libxml/parser.h>

#include <libxml/tree.h>

#include <string.h>

/* 
parses xml file in tree form using libxml and extracts envelope fields and payload from it.
how to run:-
gcc -Wall -I/usr/include/libxml2 -o test bmd_extract.c -lxml2*/
 

void extract_bmd (char * filename,  char* fields[]);
//extracts bmd file and puts the envelop and payload in array fields in order message id, message type, sender, destination, creation date time,
//sign ,reference id, payload , user properties
