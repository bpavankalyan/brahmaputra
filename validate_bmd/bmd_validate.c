/*
gcc -Wall -I/usr/include/libxml2  -o test  bmd_validate.c  `mysql_config --cflags --libs` -lxml2

The validation will be done mainly for the envelope part of the BMD.
1. The mandatory values (Sender, Destination, Message Type, etc.) must be present in the
received BMD.
2. For the received {Sender, Destination, Message Type}, there should be an active route
record present in the routes table (​ see here​ ).
3. For the selected route record, there should be corresponding records present in
transport_config and transform_config tables.
4. We will also check for some upper limit on the payload size. For example, the payload
larger than 5MB may not be allowed, or are allowed only for certain senders and message
types, etc
*/

#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <string.h>
#include <mysql.h>

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
  MYSQL *conn;

  MYSQL_ROW row;
	
  char *server = "localhost";
  char *user = "root";
  char *password = "riya"; /* set me first */
  char *database = "esb_db";
	
  conn = mysql_init(NULL);
	
  /* Connect to database */
  if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
	fprintf(stderr, "%s\n", mysql_error(conn));
	exit(1);
  }
	
  
  struct map attributes[20];
  xmlDoc *doc = NULL;
  xmlNode *root = NULL;
  xmlNode *node = NULL;
  xmlNode *payload = NULL;
  doc = xmlReadFile("bmd.xml",NULL,0);
  
  if (doc == NULL) {
    printf("wrong syntax in xml");
  }
 
  root = xmlDocGetRootElement(doc);
  node=xmlFirstElementChild(root)->children;
  
  int i=0;

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
  char * MessageID="MessageID";
  char * MessageType="MessageType";
  char * Sender="Sender";
  char * Destination="Destination";
  char * CreationDateTime="CreationDateTime";
  char * Signature="Signature";
  char * ReferenceID="ReferenceID";
  char * Payload="Payload";
  int m1=0, m2=0, m3=0, m4=0, m5=0, m6=0, m7=0, m8=0;
  for(int j=0;j<i;j++){
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
  xmlFreeDoc(doc);
 
  xmlCleanupParser();

  char  query[1000]="SELECT route_id FROM routes where sender='";
  strcat(query,Sender);
  strcat(query,"' and destination='");
  strcat(query,Destination);
  strcat(query,"' and  message_type='");
  strcat(query,MessageType); 
  strcat(query,"' and is_active=1"); 
  //printf("%s", query);
  if (mysql_query(conn, query)) 
  {
     fprintf(stderr, "%s\n", mysql_error(conn));
     exit(1);
  }
  
  MYSQL_RES *result = mysql_store_result(conn);
  
  if (result == NULL) 
  {
      printf( "For the received Sender, Destination, Message Type there are no  active route record present in the routes table \n");
      exit(1);
  }
  int num_fields = mysql_num_fields(result);

  char query2[1000]="";
  char query3[1000]="";

  while ((row = mysql_fetch_row(result))) 
  { 
      for(int i = 0; i < num_fields; i++) 
      {   
          
          printf("route id for the received Sender, Destination, Message Type : %s \n", row[i] ? row[i] : "NULL"); 
          strcat(query2,"SELECT id FROM transport_config where route_id='");
          strcat(query2,row[i]);
          strcat(query2,"'");
          strcat(query3,"SELECT id FROM transform_config where route_id='");
          strcat(query3,row[i]);
          strcat(query3,"'");

          if (mysql_query(conn, query2)) 
          {
            fprintf(stderr, "%s\n", mysql_error(conn));
            exit(1);
          }
  
          MYSQL_RES *result2 = mysql_store_result(conn);
           
          if (result2 == NULL) 
          {
                printf( "For this route id there are no record present in the transport_config table \n");
                exit(1);
          }
          if (mysql_query(conn, query3)) 
          {
            fprintf(stderr, "%s\n", mysql_error(conn));
            exit(1);
          }
  
          MYSQL_RES *result3 = mysql_store_result(conn);
  
          if (result3 == NULL) 
          {
                printf( "For this route id there are no record present in the transform_config table \n");
                exit(1);
          }
           while ((row = mysql_fetch_row(result2))) 
           { 
                for(int j = 0; j < mysql_num_fields(result2); j++) 
                {   
                    printf("transport_config id for this route id is : %s \n", row[j] ? row[j] : "NULL"); 
                }
           }
           while ((row = mysql_fetch_row(result3))) 
           { 
                for(int j = 0; j < mysql_num_fields(result3); j++) 
                {   
                    printf("transform_config id for this route id is : %s \n", row[j] ? row[j] : "NULL"); 
                }
           }


      } 

  }
  
  mysql_free_result(result);
  mysql_close(conn);
  
  exit(0);

  
}
