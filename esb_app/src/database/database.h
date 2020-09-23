#include <stdio.h>

#ifndef  DATABASE_H
#define  DATABASE_H

#define SERVER     "localhost"  /*hostname*/
#define USER       "root"       /*username*/
#define PASSWORD   "Pavan1999@" /*blank password this user*/
#define DATABASE   "esb_db"     /*name of the database*/
#define PORT        3306        /*port number*/
#define UNIX_SOCKET NULL        /*unix socket*/
#define FLAG        0           /*last parameter to mysql_real_connect*/


#define INSERT "INSERT INTO                                  \
esb_request(sender_id,dest_id,message_type,reference_id,     \
message_id,data_location,status,status_details,received_on)  \
VALUES('%s','%s','%s','%s','%s','%s','%s','%s','%s')"

#define SELECT_ACTIVE_ROUTE     "SELECT route_id FROM routes WHERE sender = '%s' AND destination = '%s' AND message_type= '%s'  AND is_active=b'1'"
#define SELECT_TRANSPORT_CONFIG "SELECT * FROM transport_config WHERE route_id='%d'"
#define SELECT_TRANSFORM_CONFIG "SELECT * FROM transform_config WHERE route_id='%d'"

#define CHECK_NEW_REQUEST "SELECT * FROM esb_request WHERE status = 'RECEIVED' LIMIT 1" 

#define UPDATE_ESB_REQUEST "UPDATE esb_request SET status = ? WHERE id = ? "   

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


typedef struct Qinfo { 
    int id;
    char * sender;
    char * destination;
    char * message_type;
    char * data_location;
}task_node_info;



int insert_to_esb_request(char *sender_id, char *dest_id,
                          char *message_type, char *reference_id, char *message_id,
                          char *data_location, char *status, char *status_details, char *received_on);

transform_config * fetch_transform_config_key_and_value(int route_id);

transport_config * fetch_transport_config_key_and_value(int route_id);

int update_esb_request (char * status, int id);

task_node_info * check_new_request(void);

int select_active_route(const char * Sender,const char * Destination, const  char * MessageType) ;

int check_id_in_transport_config(int route_id) ;
int check_id_in_transform_config(int route_id) ;
int connect_to_db(void);


#endif

/*
The data extracted from the BMD envelope element is inserted as a row in the esb_request table. The status column's value for the newly inserted row should be RECEIVED*/
