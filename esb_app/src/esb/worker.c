#include <stdio.h>

#include <unistd.h>

#include "esb.h"

#include <mysql/mysql.h>

/**
 * TODO: Implement the proper logic as per ESB specs.
 */
void * poll_database_for_new_requets(void * vargp) {
  // Step 1: Open a DB connection
  int i = 1;
  while (i ==1) {
    /**
     * Step 2: Query the esb_requests table to see if there
     * are any newly received BMD requets.
    
     */
    //start
    //query esb_request table
    MYSQL * conn;

    MYSQL_ROW row;

    char * server = "localhost";
    char * user = "root";
    char * password = "Pavan1999@"; /* set me first */
    char * database = "esb_db";

    conn = mysql_init(NULL);

    /* Connect to database */
    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
      fprintf(stderr, "%s\n", mysql_error(conn));
      return 0;
    }
    char query0[1000] = "SELECT sender_id,dest_id,message_type,data_location, id FROM esb_request where status='RECEIVED' ORDER BY id LIMIT 1";
    if (mysql_query(conn, query0)) {
      fprintf(stderr, "%s\n", mysql_error(conn));
      return 0;
    }
    char * id;
    char * Sender;
    char * Destination;
    char * MessageType;
    char * data_location;
    MYSQL_RES * result0 = mysql_store_result(conn);
    int num_fields = mysql_num_fields(result0);
    int set = 0;
    printf("checking for available request\n");
    while ((row = mysql_fetch_row(result0))) {
      set = 1;
      Sender = row[0];
      Destination = row[1];
      MessageType = row[2];
      data_location = row[3];
      id = row[4];

      /* now  mark the fetched esb request as processing*/

      char query_s[1000] = "UPDATE esb_request SET status='PROCESSING' WHERE id='";
      strcat(query_s, id);
      strcat(query_s, "'");
      if (mysql_query(conn, query_s)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 0;
      }
    }
      mysql_free_result(result0);
    //stop
    //fetched the request

    //if found a new request set will be 1
    if (set == 1) {
      /**
       * Found a new request, so we will now process it.
       * in this step. Basically, you will be doing:
       * 1. Find if there is any transformation to be applied to
       *    the payload before transporting it to destination.
       * 2. If needed, transform the request.
       * 3. Transport the transformed data to destination.
       * 4. Update the status of the request in esb_requests table
       *    to mark it as done (or error) depending on the outcomes
       *    of this step.
       * 5. Cleanup
       */
      printf("hello");
      //get the route id corresponding to sender, destination, message type
      char * route_id;
      char * transport_id;
      char * transform_id;
      char * transport_key;
      char * transport_value;
      char * transform_key;
      char * transform_value;

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
      //get the transport config key, value and transform config key, value corresponding to the route id
      while ((row = mysql_fetch_row(result))) {
        int i, j;
        for (i = 0; i < num_fields; i++) {
          route_id = row[i];
          printf("route id for the received Sender, Destination, Message Type : %s \n", row[i] ? row[i] : "NULL");
          strcat(query2, "SELECT config_key,config_value FROM transport_config where route_id='");
          strcat(query2, row[i]);
          strcat(query2, "'");
          strcat(query3, "SELECT config_key,config_value FROM transform_config where route_id='");
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
            transport_key = row[0];
            transport_value = row[1];
          }
          while ((row = mysql_fetch_row(result3))) {
            transform_key = row[0];
            transform_value = row[1];
          }
           mysql_free_result(result2);
           mysql_free_result(result3);

        }

      }
    

        mysql_free_result(result);
      //stored transport transform values
      //printf("%s",transport_key);
      
      
      char * fields[1];  //url
      apply_transform(transform_key, transport_key, transport_value, data_location,fields);

     // char* transformed_string="https://ifsc.razorpay.com/HDFC0CAGSBK";
     if (!strcmp(transport_key, "API_URL")) {
        printf("sending http request");
        
        http_request(fields[0]);


      }
      
      //char * url = "https://ifsc.razorpay.com/HDFC0CAGSBK";
       else if (!strcmp(transport_key, "SMTP")) {
         int i=sendMail("riyatoteja1998@gmail.com", "/home/riya/esb_endpoint/payload.json");

      }
      printf("Applied transformation and transporting steps.\n");

      //set the esb request as DONE in esb request table
      char query_d[1000] = "UPDATE esb_request SET status='DONE' WHERE id='";
      strcat(query_d, id);
      strcat(query_d, "'");
      if (mysql_query(conn, query_d)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 0;
      }

      mysql_close(conn);

      printf("DONE\n");

      /**
       * Sleep for polling interval duration, say, 5 second.
       * DO NOT hard code it here!
       */
     
    }
     printf("Sleeping for 5 seconds.\n");
     sleep(5);
  }
}
