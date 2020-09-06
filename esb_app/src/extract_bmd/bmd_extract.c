#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
 
/* 
parses xml file in tree form using libxml and extracts envelope fields and payload from it.
how to run:-
gcc -Wall -I/usr/include/libxml2 -o xml2json xml2json.c -lxml2*/
 
struct map{
  char * key;
  char * value;
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
 
 

 
int main(){
  struct map attributes[20];
  xmlDoc *doc = NULL;
  xmlNode *root = NULL;
  xmlNode *node = NULL;
  xmlNode *payload = NULL;
  doc = xmlReadFile("bmd.xml",NULL,0);
 
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


  for(int j=0;j<i;j++){
     printf("%s : %s\n" , attributes[j].key, attributes[j].value);
  }
  xmlFreeDoc(doc);
 
  xmlCleanupParser();
}
