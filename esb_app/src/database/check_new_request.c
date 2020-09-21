#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <mysql/mysql.h>
#include "database.h"

#define STRING_SIZE 1000


task_node_info *  check_new_request() {

    MYSQL * conn;
    MYSQL_RES * res;
    MYSQL_ROW row;
    char query[STRING_SIZE];
    conn = mysql_init(NULL);

    /* Connect to database */
   if (mysql_real_connect(conn, SERVER,USER,PASSWORD,DATABASE,PORT,UNIX_SOCKET,FLAG) == NULL) {
	    fprintf(stderr, "Error [%d]: %s \n",mysql_errno(conn),mysql_error(conn));
	    mysql_close(conn);
		return NULL;
	}  


    sprintf(query, CHECK_NEW_REQUEST);
    printf("%s\n",query);
    /* Execute SQL query.*/
    if (mysql_query(conn, query)) {
        printf("Failed to execute query. Error: %s\n", mysql_error(conn));
    }

    res = mysql_store_result(conn);

    if(res == NULL)
       return NULL;

    task_node_info * task_node= (task_node_info *) malloc(sizeof(task_node_info));

    while(row = mysql_fetch_row(res)) {  
    printf("%s\n",row[1]);
    printf("%s\n",row[2]);
    printf("%s\n",row[3]);

    task_node->id = atoi(row[0]);
    task_node->sender = row[1];
    task_node->destination = row[2];
    task_node->message_type = row[3];
    task_node->data_location = row[7];

    return task_node;

    }

   

    /* free results */
    mysql_free_result(res);
    return NULL;
}

/*
int main()
{
  task_node_info * tn = check_new_request(13);
  printf("%d\n%s\n%s\n%s\n%s\n",tn->id,tn->sender, tn->destination, tn->message_type,tn->data_location);
  return 0;
}
*/