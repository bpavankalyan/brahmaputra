/**
 * @brief Function selects active  route id in routes tables.
 * sql query: SELECT route_id FROM routes 
 *            WHERE sender = '%s' AND destination = '%s'
 *            AND message_type= '%s'  AND  is_active= 1                
 * 
 * returns route_id if active else -1.
 * 
 */
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <mysql/mysql.h>
#include "database.h"


#define STRING_SIZE 1000


/* Returns route_id if an active route exists for a given sender , destination and message type */
int select_active_route(const char * Sender, const char * Destination, const  char * MessageType) {
    int route;

    MYSQL * conn;
    MYSQL_RES * res;
    MYSQL_ROW row;
    char query[STRING_SIZE];
    conn = mysql_init(NULL);

    if (mysql_real_connect(conn, SERVER,USER,PASSWORD,DATABASE,PORT,UNIX_SOCKET,FLAG) == NULL)
    {
        fprintf(stderr, "Error [%d]: %s \n",mysql_errno(conn),mysql_error(conn));
        mysql_close(conn);
        return -1;
    }

    /* Execute SQL query to fetch all table names.*/
    sprintf(query, SELECT_ACTIVE_ROUTE, Sender, Destination, MessageType);

    if (mysql_query(conn, query)) {
        printf("Failed to execute quesry. Error: %s\n", mysql_error(conn));
        return -1;
    }
    
    printf("query is %s\n ", query);
    
    res = mysql_store_result(conn);
    if(res== NULL)
       return -1;
    if((row = mysql_fetch_row(res)))
       route = atoi(row[0]);
    else{
     printf("NO ROW\n");
     route= -1;
     }

    mysql_free_result(res);

    mysql_close(conn);


    return route;
}

/*
int main()
{
   printf("%d\n", select_active_route("756E2EAA-1D5B-4BC0-ACC4-4CEB669408DA","6393F82F-4687-433D-AA23-1966330381FE","CreditReport"));
   return 0;
}*/
