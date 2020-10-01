/**
 * @brief Function returns route_id of a route if exists by performing
 * sql query:SELECT status 
 *           FROM esb_request
 *           WHERE message_id = ?
 * 
 * returns status if message_id exists else NULL if does not exist.
 * 
 */
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <mysql/mysql.h>
#include "database.h"


/**
 * @breif check route_id in transport_config table
 * 
 * @parameters route_id in routes table
 * @return 1 for success
 *         0 for any failure
 */

int check(int route_id , char * query_name)
{
    MYSQL * conn;
    MYSQL_RES * res;
    MYSQL_ROW row;
    char query[5000];
    conn = mysql_init(NULL);

    /* Connect to database */
    if (mysql_real_connect(conn, SERVER,USER,PASSWORD,DATABASE,PORT,UNIX_SOCKET,FLAG) == NULL) {
	    fprintf(stderr, "Error [%d]: %s \n",mysql_errno(conn),mysql_error(conn));
	    mysql_close(conn);
		return 0 ;
	}  

    /* Execute SQL query to fetch all table names.*/
    sprintf(query, query_name, route_id);
    printf("%s\n", query);
    if (mysql_query(conn, query)) {
        printf("Failed to execute query. Error: %s\n", mysql_error(conn));
        return 0;
    }

    res = mysql_store_result(conn);
    if(res == NULL)
       return 0;
    int retval = mysql_num_rows(res);
    if (retval > 0) 
       return 1;
    

    /* free results */
    mysql_free_result(res);

    mysql_close(conn);

    return 0;	
}

int check_id_in_transport_config(int route_id) {

	return check(route_id,SELECT_TRANSPORT_CONFIG);
}

/*
int main()
{
   printf("%d\n", check_id_in_transport_config(15));
   printf("%d\n", check_id_in_transport_config(16));
   printf("%d\n", check_id_in_transport_config(1));

   return 0;
}
*/
