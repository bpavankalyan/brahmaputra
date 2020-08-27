/*
parse BMD file, extracts fields in envelop and payload of BMD file and store them in character strings
*/
#include <stdio.h>
#include <string.h>

#include <stdlib.h>

// Below function extracts characters present in src
// between m and n (excluding n) 
char* substr( char *src, int m, int n)
{
	// get length of the destination string
	int len = n - m;

	// allocate (len + 1) chars for destination (+1 for extra null character)
	char *dest = (char*)malloc(sizeof(char) * (len + 1));

	// start with m'th char and copy 'len' chars into destination
	strncpy(dest, (src + m), len);

	// return the destination string
	return dest;
}

char* parse (char* xml_string, char* startToken, char* endToken){
	
    
    char* p; 
  
    // Find first occurrence of s2 in s1 
    p = strstr(xml_string, startToken); 
    int index1=strlen(xml_string)-strlen(p)+strlen(startToken);
	
	
	p = strstr(xml_string, endToken); 
    int index2=strlen(xml_string)-strlen(p);
	return substr(xml_string, index1, index2 );
	
  
    
}
int main() {
    char var[100];
	char xml[1000];
	char * MessageId;
	char * MessageType;
	char * Sender;
	char * Destination;
	char * CreationDateTime;
	char * Signature;
	char * ReferenceID;
	char * Payload;
	strcpy(xml, " ");
    FILE *file;
    file = fopen("bmd.xml","r");
    while(fgets(var, sizeof(var), file)!=NULL){
        strcat(xml,var);
	}
	fclose(file);
	
	
	char s1[] = "<MessageID>"; 
    char s2[] = "</MessageID>";  
	MessageId=parse(xml, s1, s2  );
	printf("MessageId = %s\n",MessageId);
	
	char s3[] = "<MessageType>"; 
    char s4[] = "</MessageType>";  
	MessageType=parse(xml, s3, s4  );
	printf("MessageType = %s\n",MessageType);
	
	char s5[] = "<Sender>"; 
    char s6[] = "</Sender>";  
	Sender=parse(xml, s5, s6  );
	printf("Sender = %s\n",Sender);
	
	char s7[] = "<Destination>"; 
    char s8[] = "</Destination>";  
	Destination=parse(xml, s7, s8  );
	printf("Destination = %s\n",Destination);
	
	char s9[] = "<CreationDateTime>"; 
    char s10[] = "</CreationDateTime>";  
	CreationDateTime=parse(xml, s9, s10  );
	printf("CreationDateTime = %s\n",CreationDateTime);
	
	char s11[] = "<Signature>"; 
    char s12[] = "</Signature>";  
	Signature=parse(xml, s11, s12  );
	printf("Signature = %s\n",Signature);
	
	char s13[] = "<ReferenceID>"; 
    char s14[] = "</ReferenceID>";  
	ReferenceID=parse(xml, s13, s14  );
	printf("ReferenceID = %s\n",ReferenceID);
	
	char s15[] = "<Payload>"; 
    char s16[] = "</Payload>";  
	Payload=parse(xml, s15, s16  );
	printf("Payload = %s\n",Payload);
    
    return 0;
}