
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

#if 0

int main(int argc, char **argv) {
    //char *status = "4ac268c2-f658-11ea-adc1-0242ac120002";
    //char *s = get_status_info(status);
   // printf("%s",s);
   task_node_info * tn = check_new_request();
   if(tn!=NULL)
  printf("%d\n%s\n%s\n%s\n%s\n",tn->id,tn->sender, tn->destination, tn->message_type,tn->data_location);
    return 0;
}
#endif
