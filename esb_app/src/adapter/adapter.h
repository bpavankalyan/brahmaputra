
 #ifndef ADAPTER_H
 #define ADAPTER_H

 char *  call_function(const char *name, void* data ,void * data1);
 void *  email_send(void *to, void *text);
 void *  http_request(void* url,void * code);
 void *  convert_to_json(void * Payload, void * name);
 void *  insert_to_json_file(void * content, void * name);
 void *  remove_file(void* ptr,void * ptr1) ;
 void *  ftp_upload(void *asptr, void *fileptr);
 void    xml_to_json(char* xml_file, char* json_file);

 #endif
 
