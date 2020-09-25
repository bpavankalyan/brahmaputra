#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <mysql/mysql.h>
#include "database.h"


#define STRING_SIZE 500


transport_config *  fetch_transport_config_key_and_value(int route_id){

    MYSQL * conn;
    MYSQL_RES * res;
    MYSQL_ROW row;
    char query[STRING_SIZE];
    int row_count=0;
    conn = mysql_init(NULL);

    /* Connect to database */
    
	if (mysql_real_connect(conn, SERVER,USER,PASSWORD,DATABASE,PORT,UNIX_SOCKET,FLAG) == NULL) {
	    fprintf(stderr, "Error [%d]: %s \n",mysql_errno(conn),mysql_error(conn));
	    mysql_close(conn);
		return NULL ;
	}  

    /*Get transform config_value*/
    sprintf(query, FETCH_TRANSPORT_KEY_AND_VALUE, route_id);

    printf("%s\n",query);

    /* Execute SQL query.*/
    if (mysql_query(conn, query)) {
        printf("Failed to execute query. Error: %s\n", mysql_error(conn));
    }

    res = mysql_store_result(conn);

    if(res == NULL)
       return NULL;

    transport_config * tn = (transport_config * ) malloc(sizeof(transport_config));

    if(row = mysql_fetch_row(res)) {  
    row_count++;
    printf("%s\n",row[0]);
    printf("%s\n",row[1]);
    tn->config_key =strdup(row[0]);
    tn->config_value = strdup(row[1]);


    }
    /* free results */
    mysql_free_result(res);
    
    mysql_close(conn);
    
    if(row_count == 1)
        return tn;

    return NULL;

    
}   


/*
int main()
{
 transport_config * tn = fetch_transport_config_key_and_value(15);
  printf("%s\n%s\n",tn->config_key,tn->config_value);
  return 0;
}
*/
