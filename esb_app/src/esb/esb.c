#include<stdio.h>
#include "email.h"
#include "esb.h"
//#include "../extract_bmd/bmd_extract.c"
//#include "../validate_bmd/bmd_validate.c"

bmd parse_bmd_xml(char* bmd_file_path) {
    char * fields[10];
    extract_bmd(bmd_file_path, fields); 
    bmd b;
    bmd_envelop envl;
   
    envl.MessageID=fields[0];
    envl. MessageType= fields[1];
    envl.Sender= fields[2];
    envl.Destination= fields[3];
    envl.CreationDateTime= fields[4];
    envl.Signature= fields[5];
    envl.ReferenceID= fields[6];
    b.envelop = envl;
    b.payload = fields[7];
    return b;
}

int is_bmd_valid(bmd b)
{

    char * MessageType=b.envelop.MessageType;
    char * Sender=b.envelop.Sender;
    char * Destination=b.envelop.Destination;
    int  valid =validate_bmd( MessageType,  Sender, Destination);

    return valid;
}

int queue_the_request(bmd b,char* bmd_file_path)
{
    
        char * fields[10];

        fields[0] = b.envelop.MessageID;
        fields[1] = b.envelop.MessageType;
        fields[2] = b.envelop.Sender;
        fields[3] = b.envelop.Destination;
        fields[4] = b.envelop.CreationDateTime;
        fields[5] = b.envelop.Signature;
        fields[6] = b.envelop.ReferenceID;
        fields[7]= bmd_file_path;

    /** 
     * TODO: Insert the envelop data into esb_requests table,
     * and implement other logic for enqueueing the request
     * as specified in Theory of Operation.
     */
    int r=insert_esb_request (fields);
    return r;
}

/**
 * This is the main entry point into the ESB. 
 * It will start processing of a BMD received at the HTTP endpoint.
 */
int process_esb_request(char* bmd_file_path) {
    int status = 1; // 1 => OK, -ve => Errors
    printf("Handling the BMD %s\n", bmd_file_path);
    // Step 1:
    bmd b = parse_bmd_xml(bmd_file_path);

    // Step 2:
    if (!is_bmd_valid(b))
    {
       
        printf("BMD is invalid!\n");
        status = -2;
    }
    else
    {
        // Step 3:
        status = queue_the_request(b,  bmd_file_path);
    }
    
    return status;
}
