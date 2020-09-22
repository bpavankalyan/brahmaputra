

#include "../adapter/adapter.h"
#include "../extract_bmd/bmd.h"
#include "../database/database.h"


#ifndef ESB_H
#define ESB_H

int process_esb_request(char* bmd_file_path);
int queue_the_request(bmd *b,char * file_path);

#endif


#if 0
typedef struct {
    char* Sender;
    char* Destination;
    char* MessageType;
    char * MessageID;
    char * CreationDateTime;
    char * Signature;
    char * ReferenceID;

} bmd_envelop;

typedef struct {
    bmd_envelop envelope;
    char* payload;
} bmd;
#endif
