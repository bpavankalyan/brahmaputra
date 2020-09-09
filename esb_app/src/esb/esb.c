#include<stdio.h>
#include "esb.h"
#include <mysql.h>
#include "../extract_bmd/bmd_extract.c"
#include "../database/insert_esb_request.c"

/**
 * TODO: This is to be implemented separately.
 */
bmd parse_bmd_xml(char* bmd_file_path) {
    bmd b;
    char *filename="bmd.xml";
    char *fields[20];
    extract_bmd(filename, fields);
    b.envelop.MessageID= fields[0];
    b.envelop.MessageType =fields[1];
    b.envelop.Sender = fields[2];
    b.envelop.Destination=fields[3];
    b.envelop.CreationDateTime=fields[4];
    b.envelop.Signature=fields[5];
    b.envelop.ReferenceID=fields[6];
    b.envelop.Payload=fields[7];

    return b;
}

int is_bmd_valid(bmd b)
{
    int valid = 1; // 1 => vaild, -1 => invalid
    // TODO: Implement the validation logic here
     MYSQL * conn;

    MYSQL_ROW row;

    char * server = "localhost";
    char * user = "root";
    char * password = "Devika@1998"; /* set me first */
    char * database = "DB";

   conn = mysql_init(NULL);

  /* Connect to database */
  if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
    fprintf(stderr, "%s\n", mysql_error(conn));
    return 0;
  }

  char * MessageType = b.envelop.MessageType;
  char * Sender = b.envelop.Sender;
  char * Destination = bs.envelop.Destination;

  //check if route id is present for given bmd message
  char query[1000] = "SELECT route_id FROM routes where sender='";
  strcat(query, Sender);
  strcat(query, "' and destination='");
  strcat(query, Destination);
  strcat(query, "' and  message_type='");
  strcat(query, MessageType);
  strcat(query, "' and is_active=1");
  //printf("%s", query);
  if (mysql_query(conn, query)) {
    fprintf(stderr, "%s\n", mysql_error(conn));
    return 0;
  }

  MYSQL_RES * result = mysql_store_result(conn);

  int num_fields = mysql_num_fields(result);

  char query2[1000] = "";
  char query3[1000] = "";
  int k = -1;
  int p = -1;
  int q = -1;
  while ((row = mysql_fetch_row(result))) {
    int i, j;
    k++;
    for (i = 0; i < num_fields; i++) {

      printf("route id for the received Sender, Destination, Message Type : %s \n", row[i] ? row[i] : "NULL");
      strcat(query2, "SELECT id FROM transport_config where route_id='");
      strcat(query2, row[i]);
      strcat(query2, "'");
      strcat(query3, "SELECT id FROM transform_config where route_id='");
      strcat(query3, row[i]);
      strcat(query3, "'");

      if (mysql_query(conn, query2)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 0;
      }

      MYSQL_RES * result2 = mysql_store_result(conn);

      if (mysql_query(conn, query3)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 0;
      }

      MYSQL_RES * result3 = mysql_store_result(conn);

      while ((row = mysql_fetch_row(result2))) {
        p++;
        for (j = 0; j < mysql_num_fields(result2); j++) {
          printf("transport_config id for this route id is : %s \n", row[j] ? row[j] : "NULL");
        }
      }
      while ((row = mysql_fetch_row(result3))) {
        q++;
        for (j = 0; j < mysql_num_fields(result3); j++) {
          printf("transform_config id for this route id is : %s \n", row[j] ? row[j] : "NULL");
        }
      }

    }

  }
  if (k == -1) {
    printf("For the received Sender, Destination, Message Type there are no  active route record present in the routes table \n");
    valid=0;
  }
  if (p == -1) {
    printf("For this route id there are no record present in the transport_config table \n");
    valid=0;
  }
  if (q == -1) {
    printf("For this route id there are no record present in the transform_config table \n");
    valid=0;
  }
  mysql_free_result(result);
  mysql_close(conn);
  printf("validation part done\n");
  return valid;

}

int queue_the_request(bmd b)
{
    int success = 1; // 1 => OK, -1 => Error cases
    int ls = insert_to_esb_request(b.envelop.Sender,
    b.envelop.Destination,b.envelop.MessageType,
    b.envelop.ReferenceID,b.envelop.MessageID,
    "RECEIVED","received successfully",b.envelop.CreationDateTime);
    if(ls ==1)
    return success;
}

/**
 * This is the main entry point into the ESB. 
 * It will start processing of a BMD received at the HTTP endpoint.
 */
int process_esb_request(char* bmd_file_path) {
    int status = 1; // 1 => OK, -ve => Errors
    printf("Handling the BMD %s\n", bmd_file_path);
    /** TODO: 
     * Perform the steps outlined in the Theory of Operation section of
     * the ESB specs document. Each major step should be implemented in
     * a separate module. Suitable unit tests should be created for all
     * the modules, including this one.
     */
    // Step 1:
    bmd b = parse_bmd_xml(bmd_file_path);

    // Step 2:
    if (!is_bmd_valid(b))
    {
        //TODO: Process the error case
        printf("BMD is invalid!\n");
        status = -2;
    }
    else
    {
        // Step 3:
        status = queue_the_request(b);
    }
    
    return status;
}
