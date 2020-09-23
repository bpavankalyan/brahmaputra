#include <stdlib.h>
#include <stdio.h>
#include "esb.h"

#include "../extract_bmd/bmd.h"
#include "../database/database.h"
/** Module that has mysql C API functions */



int queue_the_request(bmd *b,char * file_path) {
    int success = 1; // 1 => OK, -1 => Error cases

    /**
     * @brief Implements the Query:
     * INSERT INTO                            
     * esb_request(sender_id,dest_id,message_type,reference_id,      
     * message_id,data_location,status,status_details)               
     * VALUES(?,?,?,?,?,?,?,?)
     *insert_to_esb_request(char *sender_id, char *dest_id, \
     *                   char *message_type, char *reference_id, char *message_id, \
     *                     char *data_location, char *status, char *status_details, char *received_on)
     * function returns 1 on successful insertion. 
     * function is defined in db_access module
     */
     
     printf("%s\n",b->envelope->CreationDateTime);
    int rc = insert_to_esb_request(b->envelope->Sender,
    b->envelope->Destination,b->envelope->MessageType,
    b->envelope->ReferenceID,b->envelope->MessageID,
    file_path,"RECEIVED","",b->envelope->CreationDateTime);
    if(rc ==1)
    return success;
}

/**
 * This is the main entry point into the ESB. 
 * It will start processing of a BMD received at the HTTP endpoint.
 */
int process_esb_request(char* bmd_file_path) {
    int status = 1; // 1 => OK, -ve => Errors
    printf("Handling the BMD %s\n", bmd_file_path);
    
    bmd *b = parse_bmd_xml(bmd_file_path);

    /** defined in bmd_extract module*/
    if (is_bmd_valid(b)!=1)
    {
        printf("BMD is invalid!\n");
        status = -2;
    }
    else
    {
        // Step 3:
        printf("BMD is valid!\n");
        status = queue_the_request(b,bmd_file_path);
       if(status==1) printf("Queued..!\n");
       else          printf("NOT queued!\n");
    }
    
    if(status != 1)
    {
       /* clean up the directory where we stored 
       * stored .xml file [ As we are not going 
       * to further steps] .
       */
       
      clean_dir(bmd_file_path);
    }  
    
    free_bmd(b);
        
    
    return status;
}

#if 0
int main () {
    int status = process_esb_request("../Testcases/bmd.xml");
    
    if(status != 1) {
        printf("Status[%d]: Request processing failed",status);
        return EXIT_FAILURE;
        }
        printf("Status[%d]: Request processing sucess",status);
    return 0;
 }   

#endif
