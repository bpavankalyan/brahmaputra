int process_esb_request(char* bmd_file_path);

typedef struct {
    
    char* MessageID;
    char* MessageType; 
    char* Sender; 
    char* Destination;
    char* CreationDateTime;
    char* Signature;
    char* ReferenceID;
    char* Payload;
    // TODO: Other fields
} bmd_envelop;

typedef struct {
    bmd_envelop envelop;
    char* payload;
} bmd;
