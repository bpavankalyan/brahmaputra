/**
 * @brief Function returns route_id of a route if exists by performing
 * sql query:SELECT status 
 *           FROM esb_request
 *           WHERE message_id = ?
 * 
 * returns status if message_id exists else NULL if does not exist.
 * 
 */
#include <stdio.h>
#include <string.h>
#include <stdio.h>

/* Contains necessary C functions of mysql */
#include <mysql/mysql.h>
#include <stdbool.h>
/**
 * Holds the info to connect to DB and
 * error specifying function for 
 * databse connection handle 
 */
#include "database.h"

#define STRING_SIZE 1000
#define SELECT_SAMPLE "SELECT status FROM esb_request WHERE message_id = '%s' "

char* get_status_information(char *message_id)
{  
    printf("messageID is %s\n",message_id);
    char * status;
    MYSQL * conn;
    MYSQL_RES * res;
    MYSQL_ROW row;
    int row_count=0;
    char query[STRING_SIZE];
    conn = mysql_init(NULL);

    /* Connect to database */
    
    if (mysql_real_connect(conn, SERVER,USER,PASSWORD,DATABASE,PORT,UNIX_SOCKET,FLAG) == NULL) {
	  fprintf(stderr, "Error [%d]: %s \n",mysql_errno(conn),mysql_error(conn));
	  mysql_close(conn);
	  return NULL ;
   }  

    /*Get transform config_value*/
    sprintf(query, SELECT_SAMPLE, message_id);

    printf("%s\n",query);

    /* Execute SQL query.*/
    if (mysql_query(conn, query)) {
        printf("Failed to execute query. Error: %s\n", mysql_error(conn));
    }

    res = mysql_store_result(conn);

    if(res == NULL)
       return NULL;


    if(row = mysql_fetch_row(res)) {  
    row_count++;
    status =strdup(row[0]);
    }
    /* free results */
    mysql_free_result(res);
    
    mysql_close(conn);
    
    if(row_count == 1)
        return status;

    return NULL;
}	

