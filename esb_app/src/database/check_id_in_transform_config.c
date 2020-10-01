/**
 * @brief Function returns route_id of a route if exists by performing
 * sql query:SELECT status 
 *           FROM esb_request
 *           WHERE message_id = ?
 * 
 * returns status if message_id exists else NULL if does not exist.
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <mysql/mysql.h>
#include "database.h"


/**
 * @breif check route_id in transform_config table
 * 
 * @parameters route_id in routes table
 * @return 1 for success
 *         0 for any failure
 */

int  check_id_in_transform_config(int route_id) {

    

    return check(route_id,SELECT_TRANSFORM_CONFIG);
}

/*
int main()
{
   printf("%d\n", check_id_in_transform_config(15));
   printf("%d\n", check_id_in_transform_config(16));
   printf("%d\n", check_id_in_transform_config(1));

   return 0;
}*/
