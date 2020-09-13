int process_esb_request(char* bmd_file_path);

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
    bmd_envelop envelop;
    char* payload;
} bmd;
