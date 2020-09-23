
#include <stdio.h>
#include <string.h>
#include <stdio.h>

#include <mysql/mysql.h>

#include "database.h"

int connect_to_db(void)
{
  printf(">> Connecting to database..\n");

  MYSQL *con;
    if (mysql_library_init(0, NULL, NULL)) {
    fprintf(stderr, "Could not initialize MySQL client library\n");
    return -1;
  }

  con = mysql_init(NULL);

  /**
   * @brief Prints error message incase
   * initialisation of con fails.
   */
  if (con == NULL)
  {

    fprintf(stderr, "mysql_init() failed.Please try again\n");
    return -1;
  }

  /**
   * @brief Checks if connection is 
   * properly established.
   * 
   */
 if (mysql_real_connect(con, SERVER,USER,PASSWORD,DATABASE,PORT,UNIX_SOCKET,FLAG) == NULL) {
	    fprintf(stderr, "Error [%d]: %s \n",mysql_errno(con),mysql_error(con));
	    mysql_close(con);

	
  return 1;
}}

