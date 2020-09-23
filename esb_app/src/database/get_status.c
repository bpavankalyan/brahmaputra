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
#define SELECT_SAMPLE "SELECT status FROM esb_request WHERE message_id = ? "

char* get_status_info(char *message_id)
{  
       printf("messageID is %s\n",message_id);
       char * status;
       MYSQL_STMT    *stmt;
       MYSQL_BIND    input_bind[1];
       unsigned long input_length;
       int           id;
	MYSQL_BIND    bind[2];
	MYSQL_RES     *prepare_meta_result;
	unsigned long length[2];
	int           param_count, column_count, row_count;
	short         small_data;
	int           int_data;
	char          str_data[2][STRING_SIZE];
	bool          is_null[2];
	
	
	MYSQL * mysql;

       mysql = mysql_init(NULL);
         
       if (mysql == NULL) {
           fprintf(stderr, "mysql_init() failed\n");
	    return NULL;
       }  
   
       if (mysql_real_connect(mysql, SERVER,USER,PASSWORD,DATABASE,PORT,UNIX_SOCKET,FLAG) == NULL) {
	    fprintf(stderr, "Error [%d]: %s \n",mysql_errno(mysql),mysql_error(mysql));
	    mysql_close(mysql);
	    return NULL;
       }  
        
	/* Prepare a SELECT query to fetch data from test_table */
	stmt = mysql_stmt_init(mysql);
	if (!stmt)
	{
	  fprintf(stderr, " mysql_stmt_init(), out of memory\n");
	    return NULL;
	}
	if (mysql_stmt_prepare(stmt, SELECT_SAMPLE, strlen(SELECT_SAMPLE)))
	{
	  fprintf(stderr, " mysql_stmt_prepare(), SELECT failed\n");
	  fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
	    return NULL;
	}
	fprintf(stdout, " prepare, SELECT successful\n");

	/* Get the parameter count from the statement */
	param_count= mysql_stmt_param_count(stmt);
	fprintf(stdout, " total parameters in SELECT: %d\n", param_count);

	if (param_count != 1) /* validate parameter count */
	{
	  fprintf(stderr, " invalid parameter count returned by MySQL\n");
	    return NULL;
	}

	/* Fetch result set meta information */
	prepare_meta_result = mysql_stmt_result_metadata(stmt);
	if (!prepare_meta_result)
	{
	  fprintf(stderr,
		 " mysql_stmt_result_metadata(), returned no meta information\n");
	  fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
	    return NULL;
	}

	/* Get total columns in the query */
	column_count= mysql_num_fields(prepare_meta_result);
	fprintf(stdout, " total columns in SELECT statement: %d\n", column_count);

	if (column_count != 1) /* validate column count */
	{
	    fprintf(stderr, " invalid column count returned by MySQL\n");
	    return NULL;
	}


        memset(input_bind, 0, sizeof(input_bind));

        /* STRING COLUMN MESSAGE_ID  */
        bind[0].buffer_type= MYSQL_TYPE_STRING;
	bind[0].buffer= (char *)str_data[1];
	bind[0].buffer_length= STRING_SIZE;
	bind[0].is_null= 0;
	bind[0].length= &length[1];


       /* Bind the buffers */
       if (mysql_stmt_bind_param(stmt, input_bind))
       {
            fprintf(stderr, " mysql_stmt_bind_param() failed\n");
	    fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
	    return NULL;
       }


       strncpy(str_data[1], message_id, STRING_SIZE);
       length[1]= strlen(str_data[1]);
 
	/* Execute the SELECT query */
	if (mysql_stmt_execute(stmt))
	{
	    fprintf(stderr, " mysql_stmt_execute(), failed\n");
	    fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
	    return NULL;
	}

	/* Bind the result buffers for all 4 columns before fetching them */

	memset(bind, 0, sizeof(bind));
	
	/* STATUS  COLUMN */
	bind[0].buffer_type= MYSQL_TYPE_STRING;
	bind[0].buffer= (char *)str_data[0];
	bind[0].buffer_length= STRING_SIZE;
	bind[0].is_null= &is_null[0];
	bind[0].length= &length[0];


	/* Bind the result buffers */
	if (mysql_stmt_bind_result(stmt, bind))
	{
	    fprintf(stderr, " mysql_stmt_bind_result() failed\n");
	    fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
	    return NULL;
	}

	/* Now buffer all results to client */
	if (mysql_stmt_store_result(stmt))
	{
	     fprintf(stderr, " mysql_stmt_store_result() failed\n");
	     fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
	     return NULL;
	}

	/* Fetch all rows */
	row_count= 0;
	fprintf(stdout, "Fetching results ...\n");
	if (!mysql_stmt_fetch(stmt))
	{
	   row_count++;
	   fprintf(stdout, "  row %d\n", row_count);
	   status=strdup(str_data[0]);
	   printf("status is%s ",status);
	}

	
	/* Free the prepared result metadata */
	mysql_free_result(prepare_meta_result);


	/* Close the statement */
	if (mysql_stmt_close(stmt))
	{
	  fprintf(stderr, " failed while closing the statement\n");
	  fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
	  return NULL;
	}
	
	if(row_count == 1)  return status;
	
	return NULL;
}	

