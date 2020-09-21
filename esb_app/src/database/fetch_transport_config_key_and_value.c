#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <mysql.h>
#include "database.h"


#define STRING_SIZE 500


void  fetch_transport_config_key_and_value(int route_id, char * key, char * value){

    MYSQL * conn;
    MYSQL_RES * res;
    MYSQL_ROW row;
    char query[STRING_SIZE];
    conn = mysql_init(NULL);

    /* Connect to database */
    
	if (mysql_real_connect(conn, SERVER,USER,PASSWORD,DATABASE,PORT,UNIX_SOCKET,FLAG) == NULL) {
	    fprintf(stderr, "Error [%d]: %s \n",mysql_errno(conn),mysql_error(conn));
	    mysql_close(conn);
		return ;
	}  

    /*Get transform config_value*/
    sprintf(query, FETCH_TRANSPORT_KEY_AND_VALUE, route_id);

    printf("%s\n",query);

    /* Execute SQL query.*/
    if (mysql_query(conn, query)) {
        printf("Failed to execute query. Error: %s\n", mysql_error(conn));
    }

    res = mysql_store_result(conn);

    while(row = mysql_fetch_row(res)) {  
    printf("%s\n",row[0]);
    printf("%s\n",row[1]);
    strcpy(key, strdup(row[0]));
    strcpy(value, strdup(row[1]));
    }
    /* free results */
    mysql_free_result(res);
}   


/*
int main()
{
  char  key[100];
  char value[100];  
  fetch_transport_config_key_and_value(1,key,value);
  printf("%s\n%s\n",key,value);
  return 0;
}
*/