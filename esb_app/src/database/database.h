#include <stdio.h>

#define  DATABASE_H

#define SERVER     "localhost"  /*hostname*/
#define USER       "root"       /*username*/
#define PASSWORD   "Pavan1999@" /*blank password this user*/
#define DATABASE   "esb_db"     /*name of the database*/
#define PORT        3306        /*port number*/
#define UNIX_SOCKET NULL        /*unix socket*/
#define FLAG        0           /*last parameter to mysql_real_connect*/


#define INSERT_INTO_ESB_REQUEST "INSERT INTO esb_request(sender_id,dest_id,message_type,reference_id,message_id,received_on,data_location,status,status_details) VALUES ('%s','%s','%s','%s','%s','%s','%s','%s',%s')"
#define SELECT_ACTIVE_ROUTE     "SELECT route_id FROM routes WHERE sender = '%s' AND destination = '%s' AND message_type= '%s'  AND is_active=b'1'"
#define SELECT_TRANSPORT_CONFIG "SELECT * FROM transport_config WHERE route_id='%d'"
#define SELECT_TRANSFORM_CONFIG "SELECT * FROM transform_config WHERE route_id='%d'"

#define CHECK_NEW_REQUEST "SELECT * FROM esb_request WHERE status = 'RECEIVED' AND id= %d LIMIT 1" 

#define UPDATE_ESB_REQUEST "UPDATE esb_request SET status = ? WHERE id = ? "   

#define GET_routeid "SELECT route_id FROM routes WHERE sender = '%s' AND destination = '%s' AND message_type= '%s'"
#define FETCH_TRANSFORM_KEY_AND_VALUE "SELECT config_key,config_value FROM transform_config WHERE route_id= %d "
#define FETCH_TRANSPORT_KEY_AND_VALUE "SELECT config_key,config_value FROM transport_config WHERE route_id=  %d "

typedef struct transport_config_data
{
    char * config_key;
    char * config_value;
}transport_config;

typedef struct transform_config_data
{
    char * config_key;
    char * config_value;
}transform_config;

int insert_esb_request (char * bmd);

void  fetch_transform_config_key_and_value(int route_id,char *key, char *value);

void fetch_transport_config_key_and_value(int route_id, char * key, char * value);

int update_esb_request (char * status, int id);


/*
The data extracted from the BMD envelope element is inserted as a row in the esb_request table. The status column's value for the newly inserted row should be RECEIVED*/
