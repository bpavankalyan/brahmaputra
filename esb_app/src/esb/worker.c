#include <stdio.h>
#include <unistd.h>
#include "esb.h"
#include "../adapter/adapter.h"
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
// #include "../task_queue/task_queue.h"
#include "../database/database.h"
#include "../extract_bmd/bmd.h"



pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
/**
* @brief  query the DB for this, and populate the 
*         request pointer with the requests.
* @return task node containing sender, destination
*         data_location
**/


task_node_info *  fetch_new_request_from_db()
{

    // select_info picks up the oldest row in esb_request table 
    printf("Checking for new requests in esb_requests table.\n");
    task_node_info * tn ;
    if(( tn = check_new_request()) != NULL){
         return tn; 
    }
    
    return NULL;     
}

void update_as_error(int id)
{
    update_esb_request("ERROR",id);  
    
}


/**
 *  Implement the proper logic as per ESB specs.
 */
void *poll_database_for_new_requests(void *vargp)
{
   printf("||------------------------------------------------||\n");
   printf("  starting thread \n");
   printf("||------------------------------------------------||\n");

   int i = 0;
   while (1)
   {
        i++;
        task_node_info * tn;
        char * content;
        char * transform_file_name; 
        char * file_name;
        bmd * bd1 ;


        pthread_mutex_lock(&lock);
        tn=fetch_new_request_from_db();
        if(tn==NULL)
        {
          printf("NO REQUESTS AVAILABLE\n");
          pthread_mutex_unlock(&lock);
        }  
      
      else{
               printf("%d\n",tn->id);
              
               update_esb_request("PROCESSING",tn->id);
               pthread_mutex_unlock(&lock);
               
               
               int id = select_active_route(tn->sender,tn->destination,tn->message_type);
               printf("id is %d \n",id);
               
               printf("Applying transformation and transporting steps.\n");
               transport_config * tp = fetch_transport_config_key_and_value(id);
	       transform_config * tf= fetch_transform_config_key_and_value(id);
               
               printf("data->location is %s\n ",tn->data_location);

               bd1 = parse_bmd_xml(((char *)tn->data_location));

               printf("%s\n%s\n-----\n%s\n%s\n",tf->config_key,tf->config_value,tp->config_key,tp->config_value);         
               if((tp!=NULL)) 
               {
                if (((strcmp(tf->config_value,"string"))==0))
                {           
                  content = call_function(tp->config_key,tp->config_value,bd1->payload);
                  printf("content is \n %s\n",content);
                  if((strcmp(content,"NO"))==0){
                        update_as_error(tn->id);
                        goto cleanup;
                  }
                  file_name =  (char *) call_function("insert_to_json_file",content,bd1->payload); 
               }
                            
                
                else{
	           printf("WITH TRANSFORMATION\n");
                  transform_file_name = call_function(tf->config_key,bd1->payload,tf->config_value);
                  call_function(tp->config_key,tp->config_value,transform_file_name); 
                  content = call_function(tp->config_key,tp->config_value,bd1->payload);
                  printf("content is \n %s\n",content);
                  file_name =  (char *) call_function("insert_to_json_file",content,bd1->envelope->MessageID);
                  printf("%s\n", (char *) call_function("remove",transform_file_name ,NULL));
                  free(transform_file_name);
               }
               
               printf("%s\n",file_name);
               if(((strcmp(((char *)call_function("email","Testmailchenab1@gmail.com",file_name)) ,"NO"))!=0)
                     && ((strcmp(((char *)call_function("ftp",bd1->payload,file_name)) ,"NO"))!=0))
                  {
                     printf("sent the json file of destination service\n");
                      update_esb_request("DONE",tn->id) ;
                  }
                  else{
                       printf("----------\nemail not sent\n-------------------\n");
                       update_as_error(tn->id);   
                  }
                  printf("%s\n", (char *) call_function("remove",file_name ,NULL));
               
             }
             
            
            /* clean up the variables stored in heap*/
cleanup:            
            free_bmd(bd1);
            free_transform_config(tf);
            free_transport_config(tp);
            free(content);
            free(file_name);
            free_request(tn);

      }
       
        /**
         * Sleep for polling interval duration, say, 5 second.
         */
        printf("||---------------------------------||\n");
        printf("Sleeping for 5 seconds\n");
        printf("||-----------------------------------||\n");

        sleep(5);

   }
}
