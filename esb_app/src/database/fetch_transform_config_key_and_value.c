#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <mysql/mysql.h>
#include "database.h"


#define STRING_SIZE 500


transform_config *  fetch_transform_config_key_and_value(int route_id){

    MYSQL * conn;
    MYSQL_RES * res;
    MYSQL_ROW row;
    char query[STRING_SIZE];
    conn = mysql_init(NULL);

    /* Connect to database */
    
	if (mysql_real_connect(conn, SERVER,USER,PASSWORD,DATABASE,PORT,UNIX_SOCKET,FLAG) == NULL) {
	    fprintf(stderr, "Error [%d]: %s \n",mysql_errno(conn),mysql_error(conn));
	    mysql_close(conn);
		return NULL ;
	}  

    /*Get transform config_value*/
    sprintf(query, FETCH_TRANSFORM_KEY_AND_VALUE, route_id);

    printf("%s\n",query);

    /* Execute SQL query.*/
    if (mysql_query(conn, query)) {
        printf("Failed to execute query. Error: %s\n", mysql_error(conn));
        return NULL;
    }

    res = mysql_store_result(conn);

    if(res == NULL)
       return NULL;

    transform_config * tn = (transform_config * ) malloc(sizeof(transform_config));

    while(row = mysql_fetch_row(res)) {  
    printf("%s\n",row[0]);
    printf("%s\n",row[1]);
    tn->config_key =strdup(row[0]);
    tn->config_value = strdup(row[1]);

    return tn;
    }
    /* free results */
    mysql_free_result(res);

    return NULL;

    
}   


/*
int main()
{
 transform_config * tn = fetch_transform_config_key_and_value(15);
  printf("%s\n%s\n",tn->config_key,tn->config_value);
  return 0;
}
*/