#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "bmd.h"
#include <string.h>
#include <libxml/parser.h>
#include "../database/database.h"

/**********************************************************************************************
*  @ brief : validating bmd request
*  input : filepath output yes/no
*  validating bmd request under 4 conditions
* 1.The mandatory values (Sender, Destination, Message Type, etc.) must be present in the
*    received BMD.
* 2. For the received {Sender, Destination, Message Type}, there should be an active route
*    record present in the routes table (​ see here​ ).
* 3. For the selected route record, there should be corresponding records present in
*    transport_config and transform_config tables.
* 4. We will also check for some upper limit on the payload size. For example, the payload
*    larger than 5MB may not be allowed, or are allowed only for certain senders and message
*    types, etc. 
*
************************************************************************************************/




int  is_bmd_valid(bmd  * bd)
{
   

 // char * sender=bd->envelope->Sender;
 // char * destination=bd->envelope->Destination;
 // char * message_type= bd->envelope->MessageType;
   

  printf("%s\n%s\n%s\n",bd->envelope->Sender,bd->envelope->Destination, bd->envelope->MessageType);
  if(validate_xml_file(bd)){
  int id =select_active_route(bd->envelope->Sender, bd->envelope->Destination, bd->envelope->MessageType); 
  printf("id is %d\n",id);                                
    if(id > 0 ){
      if(check_id_in_transform_config(id) >=0  &&  check_id_in_transport_config(id) >=0 ){
          if(strlen(bd->payload) <= 5242880)
            return 1;
      } 
    }
  }     
   
    return 0;                                         
}



/* @ brief: validating bmd xml .
 * checking whether xml file consists of all appropriate elements.
 * if it contains returns 1
 * else return 0
*/



int validate_xml_file( bmd * bmd_file)
{
  /* MessageID */
  if(bmd_file->envelope->MessageID  == NULL || (strcmp(bmd_file->envelope->MessageID,"")==0)) {
    fprintf(stderr,"Message ID doesnot exist in bmd\n");
    return 0;
  }

  /* MessageType */
  if(bmd_file->envelope->MessageType == NULL || (strcmp(bmd_file->envelope->MessageType,"")==0)) {
    fprintf(stderr,"Message Type doesnot exist in bmd\n");
    return 0;
  }

  /* Sender */
  if(bmd_file->envelope->Sender == NULL || (strcmp(bmd_file->envelope->Sender,"")==0)) {
    fprintf(stderr,"Sender doesnot exist in bmd\n");
    return 0;
  }


  /* Destination */
  if(bmd_file->envelope->Destination == NULL || (strcmp(bmd_file->envelope->Destination,"")==0)) {
    fprintf(stderr,"Destination doesnot exist in bmd\n");
    return 0;
  }


  /* CreationDateTime */
  if(bmd_file->envelope->CreationDateTime == NULL || (strcmp(bmd_file->envelope->CreationDateTime,"")==0)) {
    fprintf(stderr,"CreationDateTime doesnot exist in bmd\n");
    return 0;
  }


  /* Signature */
  if(bmd_file->envelope->Signature == NULL || (strcmp(bmd_file->envelope->Signature,"")==0)) {
    fprintf(stderr,"Signature doesnot exist in bmd\n");
    return 0;
  }

  /* ReferenceID */
  if(bmd_file->envelope->ReferenceID == NULL || (strcmp(bmd_file->envelope->ReferenceID,"")==0)) {
      fprintf(stderr,"ReferenceID doesnot exist in bmd\n");
      return 0;
  }

  /* payload */
  if(bmd_file->payload == NULL || (strcmp(bmd_file->payload,"")==0)) {
    fprintf(stderr,"Payload doesnot exist in bmd\n");
    return 0;
  }

  return 1;
}






