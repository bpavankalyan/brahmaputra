#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>
int main() {
	MYSQL *conn;
	char *server = "localhost";
	char *user = "root";
	char *password = "Devika@1998"; /* set me first */
	char *database = "DB";
	
	conn = mysql_init(NULL);
	
	/* Connect to database */
	if (!mysql_real_connect(conn, server, user, password, 
                                      database, 0, NULL, 0)) {
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}
	printf("success");
	return EXIT_SUCCESS;
	}
	
	



