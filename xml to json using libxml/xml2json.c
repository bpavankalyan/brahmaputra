#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
 
/* 
reference from
https://qnaplus.com/print-xml-file-tree-form-libxml2-c-programming/
how to run:-
gcc -Wall -I/usr/include/libxml2 -o xml2json xml2json.c -lxml2*/
 
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
 
void print_xml(xmlNode * node, int indent_len)
{
    int i=0;
    while(node)
    {   
        if(node->type == XML_ELEMENT_NODE)
        { 
          if(is_leaf(node)){
             i++;
             printf("%*c\"%s\": \"%s\"", indent_len*2, ' ', node->name, xmlNodeGetContent(node));
	     if(node->next != NULL)printf(",\n");
           }
          else{

             printf("%*c\"%s\": {\n", indent_len*2, ' ', node->name);
             
             print_xml(node->children, indent_len + 1);
          }
        }
        //print_xml(node->children, indent_len + 1);
        
        node = node->next;
    }
    if(i>1)printf("%*c,\n", indent_len*2 -1,'}');
    else printf("%*c\n", indent_len*2 -1,'}');
    
}
 
int main(){
  xmlDoc *doc = NULL;
  xmlNode *root_element = NULL;
 
  doc = xmlReadFile("dummy.xml",NULL,0);
 
  if (doc == NULL) {
    printf("Could not parse the XML file");
  }
 
  root_element = xmlDocGetRootElement(doc);
  printf("{\n");
  print_xml(root_element, 1);

  xmlFreeDoc(doc);
 
  xmlCleanupParser();
}
