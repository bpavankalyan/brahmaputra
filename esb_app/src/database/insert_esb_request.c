#include <mysql/mysql.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../extract_bmd/bmd.h"
#include "database.h"

 int insert_to_esb_request(char * Sender,
    char * Destination,char * MessageType,
    char * ReferenceID,char * MessageID,
    char * file_path,char * status ,char * status_details ,char * CreationDateTime)
{    
    int success = 1; //1=>success , -ve for errors

    MYSQL * conn;
    MYSQL_RES * res;
    MYSQL_ROW row;

    int8_t received_temp[100]; // eg: "2020-08-12 05:18:00+0000";
    int8_t received_on[100];
    strcpy(received_temp, CreationDateTime);

    /*Changing DateTime format*/
    int n = strlen(received_temp);
    int j = 0;
    for (int i = 0; i <= n && received_temp[i] != '+'; i++) {
         
        received_on[j] = received_temp[i];
        if (received_on[i] == 'T') //test for character
        {
            received_on[i] = ' '; // change T to space
        }
        if (i == n - 3) {
            char ch = ':';
            strncat(received_on, & ch, 1);
            j++;
        }
        j++;
    }
    
    printf("rece %s\n",received_on);

    conn = mysql_init(NULL);

    /* Connect to database */
    if (mysql_real_connect(conn, SERVER,USER,PASSWORD,DATABASE,PORT,UNIX_SOCKET,FLAG) == NULL) {
	    fprintf(stderr, "Error [%d]: %s \n",mysql_errno(conn),mysql_error(conn));
	    mysql_close(conn);
		return -1;
	} 

    /*sql query to insert in table*/

    char query1[5000];
    char query2[5000];
    int check = 1; //checking for duplicacy

    sprintf(query1, INSERT, Sender, Destination,
         MessageType,
        ReferenceID,
        MessageID, file_path,
         status,status_details, received_on);

    printf("\n\n%s\n\n", query1);

    if (mysql_query(conn, query1)) {
        printf("Failed to execute query.Error: %s\n", mysql_error(conn));
        success = -1;
        return success;
    }

    res = mysql_use_result(conn);

    /*free the result*/

    mysql_free_result(res);
    mysql_close(conn);
    return success;
}
/*
int main()
{
  char *s,*d,*mt,*rid,*mid,*dl,*st,*std;
  s="sender2"; d = "dest3"; mt = "CreditReports"; mid = "2";
  dl = "dat_loc"; st ="Active"; std="process";
  rid = "ref_id1";
 insert_to_esb_request(s,d,mt,rid,mid,dl,st,std,"2020-08-12T05:18:00+00001");
 return 0;
}*/


