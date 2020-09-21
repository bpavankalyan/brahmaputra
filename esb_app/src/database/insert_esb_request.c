/*
gcc -Wall -I/usr/include/libxml2  -o test  insert_esb_request.c  `mysql_config --cflags --libs` -lxml2

The data extracted from the BMD envelope element is inserted as a row in the esb_request table. The status column's value for the newly inserted row should be RECEIVED 
*/
#include <stdio.h>
#include <string.h>
#include <mysql/mysql.h>
 

 
int insert_esb_request (char * fields[]){

  
  MYSQL *conn;

  MYSQL_ROW row;
	
  char *server = "localhost";
  char *user = "root";
  char *password = "Pavan1999@"; /* set me first */
  char *database = "esb_db";
	

  conn = mysql_init(NULL);
	
  /* Connect to database */
  if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
	fprintf(stderr, "%s\n", mysql_error(conn));
	return 0;
  }
	
  
  
  
  char * MessageID=fields[0];
  char * MessageType=fields[1];
  char * Sender=fields[2];
  char * Destination=fields[3];
  char * CreationDateTime=fields[4];
  char * Signature=fields[5];
  char * ReferenceID=fields[6];
  char * Payload=fields[7];
	
/*insert the fields into esb request table*/
  char  query[1000]="INSERT INTO                                  \
esb_request(sender_id,dest_id,message_type,reference_id,     \
message_id,received_on,status, status_details, data_location)  \
VALUES( '";


  strcat(query,Sender);
  strcat(query,"','");
  strcat(query,Destination);
  strcat(query,"','");
  strcat(query,MessageType); 
  strcat(query,"','");
  strcat(query,ReferenceID);
  strcat(query,"','");
  strcat(query,MessageID);
  strcat(query,"','");
  strcat(query,CreationDateTime); 
  strcat(query,"', 'RECEIVED','received successfully', 'Routes')");
  


  printf("%s\n", query);
  if (mysql_query(conn, query)) 
  {
     fprintf(stderr, "%s\n", mysql_error(conn));
     return 0;
  }


  mysql_close(conn);
  printf("insertion in esb_request table done\n");
  return 1;

  
}


int main()
{
  char * fields[] = {"ASSSS","SSSS","ass888a","asasa88","2020-08-12T05:18:00+0000","ggg","RECEIVED","received successfully", "Routes"};
  insert_esb_request(fields);
  return 0;
}



