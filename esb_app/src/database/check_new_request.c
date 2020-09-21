#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <mysql.h>
#include "database.h"


int check_new_request(int id, char * sender, char * destination, char * message_type) {
    int success = 1;
    int failure = -1;

    MYSQL * conn;
    MYSQL_RES * res;
    MYSQL_ROW row;
    char query[5000];
    conn = mysql_init(NULL);

    /* Connect to database */
    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        printf("Failed to connect MySQL Server %s. Error: %s\n", server, mysql_error(conn));
    }

    sprintf(query, CHECK_NEW_REQUEST, id);
    /* Execute SQL query.*/
    if (mysql_query(conn, query)) {
        printf("Failed to execute query. Error: %s\n", mysql_error(conn));
    }

    res = mysql_store_result(conn);
    int retval = mysql_num_rows(res);
    if (retval == 1) {
        return success;
    }

    /* free results */
    mysql_free_result(res);
    return failure;
}