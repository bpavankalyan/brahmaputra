#include <libxml/tree.h>

#include <stdio.h>

#include <sys/types.h>

#include <unistd.h>

#include <string.h>

#include "xml2json.c"

int main(){
  char* input="bmd.xml";
  char * output="bmd2.json";
  printf("%s generated successfully\n", output);
  xml_to_json(input, output);
  return 0;

