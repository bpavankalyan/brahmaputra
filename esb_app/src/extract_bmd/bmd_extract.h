#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <string.h>
 
/* 
parses xml file in tree form using libxml and extracts envelope fields and payload from it.
how to run:-
gcc -Wall -I/usr/include/libxml2 -o test bmd_extract.c -lxml2*/
 
struct map{
  char*  key;
  char* value;
};

int is_leaf(xmlNode * node)
{
  xmlNode * child = node->children;
  while(child)
  {
    if(child->type == XML_ELEMENT_NODE) return 0;
 
    child = child->next;
  }
 
  return 1;
}
 
 //, char* MessageID,char* MessageType,char* Sender,char* Destination,char* CreationDateTime,char* Signature,char* ReferenceID, char* Payload

 
void extract_bmd (char * filename,  char* fields[]){
  struct map attributes[20];
  xmlDoc *doc = NULL;
  xmlNode *root = NULL;
  xmlNode *node = NULL;
  xmlNode *payload = NULL;
  doc = xmlReadFile(filename,NULL,0);

  char * MessageID="MessageID";
  char * MessageType="MessageType";
  char * Sender="Sender";
  char * Destination="Destination";
  char * CreationDateTime="CreationDateTime";
  char * Signature="Signature";
  char * ReferenceID="ReferenceID";
  char * Payload="Payload";
  char* UserProperties="UserProperties";
  if (doc == NULL) {
    printf("invalid xml format");
  }
 
  root = xmlDocGetRootElement(doc);
 //extracts envelope node
  node=xmlFirstElementChild(root)->children;
  
  int i=0;
  //print_xml(root_element, 1);
  while(node)
    {   
        if(node->type == XML_ELEMENT_NODE)
        {    
           attributes[i].key=(char *)node->name;
           attributes[i].value=(char *) xmlNodeGetContent(node);
           i++; 
        }       
        node = node->next;
    }
 //extracts payload node
  payload=xmlLastElementChild(root);
   while(payload)
    {   
        if(payload->type == XML_ELEMENT_NODE)
        {    
           attributes[i].key=(char *)payload->name;
           attributes[i].value=(char *) xmlNodeGetContent(payload);
           i++; 
        }  
        payload = payload->next;
    }

  
  int u=-1;
  int m1=0, m2=0, m3=0, m4=0, m5=0, m6=0, m7=0, m8=0, m9=0;
  int j;
  for(j=0;j<i;j++){
     char * s= attributes[j].key;
     if(strcmp(MessageID,s)==0){
       m1=1;
       MessageID=attributes[j].value;
     }
     if(strcmp(MessageType,s)==0){
       m2=1;
       MessageType=attributes[j].value;
     }
     if(strcmp(Sender,s)==0){
       m3=1;
       Sender=attributes[j].value;
     }
     if(strcmp(Destination,s)==0){
       m4=1;
       Destination=attributes[j].value;
     }
     if(strcmp(CreationDateTime,s)==0){
       m5=1;
       CreationDateTime=attributes[j].value;
     }
     if(strcmp(Signature,s)==0){
       m6=1;
       Signature=attributes[j].value;
     }
     if(strcmp(ReferenceID,s)==0){
       m7=1;
       ReferenceID=attributes[j].value;
     }
     if(strcmp(Payload,s)==0){
       m8=1;
       Payload=attributes[j].value;
     }
     if(strcmp(UserProperties,s)==0){
       m9=1;
       u=j;
       UserProperties=attributes[j].value;
     }
    
     
     
  }
  if(m1==0){
    printf("%s field is not present in BMD File", MessageID);
  }
  if(m2==0){
    printf("%s field is not present in BMD File", MessageType);
  }
  if(m3==0){
    printf("%s field is not present in BMD File", Sender);
  }
  if(m4==0){
    printf("%s field is not present in BMD File", Destination);
  }
  if(m5==0){
    printf("%s field is not present in BMD File", CreationDateTime);
  }
  if(m6==0){
    printf("%s field is not present in BMD File", Signature);
  }
  if(m7==0){
    printf("%s field is not present in BMD File", ReferenceID);
  }
  if(m8==0){
    printf("%s field is not present in BMD File", Payload);
  }
  if(m1==1 && m2==1 && m3==1 && m4==1 && m5==1 && m6==1 && m7==1 && m8==1) 
    printf("All mandatory fields are present in BMD\n");
  else exit(1);

  
  fields[0]= MessageID;
  fields[1]= MessageType;
  fields[2]= Sender;
  fields[3]= Destination;
  fields[4]= CreationDateTime;
  fields[5]= Signature;
  fields[6]= ReferenceID;
  fields[7]= Payload;
  if(u!=-1 && m9==1) fields[8]=UserProperties;

  xmlFreeDoc(doc);
 
  xmlCleanupParser();

}

