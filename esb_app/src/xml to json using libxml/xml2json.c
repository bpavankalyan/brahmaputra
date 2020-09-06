#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <sys/types.h>
#include <unistd.h>
/* 
takes in xml file and uses libxml to convert it in a tree like data structure and then prints in json format using libxml.

how to run:-
gcc -Wall -I/usr/include/libxml2 -o xml2json xml2json.c -lxml2*/
 

//checks whether a node is leaf node
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

 // takes the root node and recursively prints in json format
void xml2json(xmlNode * node, int indent_len)
{
    int i=0;
    while(node)
    {   
        if(node->type == XML_ELEMENT_NODE)
        { 
          if(is_leaf(node)){
             i++;
             printf("%*c\"%s\": \"%s\"", indent_len*2, ' ', node->name, xmlNodeGetContent(node));
	     if(node->next->next)printf(",\n");
             else printf("\n");
           }
          else{

             printf("%*c\"%s\": {\n", indent_len*2, ' ', node->name);
             
             xml2json(node->children, indent_len + 1);
             if(!node->next)printf("%*c\n", (indent_len+1)*2 -1,'}');
             else if(node->next->next)printf("%*c,\n", (indent_len+1)*2 -1,'}');
             else printf("%*c\n", (indent_len+1)*2 -1,'}');
          }
        }
        //print_xml(node->children, indent_len + 1);
        
        node = node->next;
    }
    //if(i>1)printf("%*c,\n", indent_len*2 -1,'}');
    //else printf("%*c\n", indent_len*2 -1,'}');
    
}
 
int main(){
  
  xmlDoc *doc = NULL;
  xmlNode *root_element = NULL;
 
  doc = xmlReadFile("bmd.xml",NULL,0);
 
  if (doc == NULL) {
    printf("Could not parse the XML file");
  }

  root_element = xmlDocGetRootElement(doc);
  printf("{\n");
  xml2json(root_element, 1);
  printf("}\n");

  xmlFreeDoc(doc);
  xmlCleanupParser();
}
