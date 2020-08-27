/*
converts a BMD XML file to JSON */
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
	char * MessageID;
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
	MessageID=parse(xml, s1, s2);
	printf(" ");
	
	char s3[] = "<MessageType>"; 
    char s4[] = "</MessageType>";  
	MessageType=parse(xml, s3, s4  );
	
	
	char s5[] = "<Sender>"; 
    char s6[] = "</Sender>";  
	Sender=parse(xml, s5, s6  );
	
	
	char s7[] = "<Destination>"; 
    char s8[] = "</Destination>";  
	Destination=parse(xml, s7, s8  );
	
	
	char s9[] = "<CreationDateTime>"; 
    char s10[] = "</CreationDateTime>";  
	CreationDateTime=parse(xml, s9, s10  );
	
	
	char s11[] = "<Signature>"; 
    char s12[] = "</Signature>";  
	Signature=parse(xml, s11, s12  );
	
	
	char s13[] = "<ReferenceID>"; 
    char s14[] = "</ReferenceID>";  
	ReferenceID=parse(xml, s13, s14  );
	
	
	char s15[] = "<Payload>"; 
    char s16[] = "</Payload>";  
	Payload=parse(xml, s15, s16  );
	
	
	FILE *fptr;

    // use appropriate location if you are using MacOS or Linux
    fptr = fopen("bmd_file.json","w");
	
	if(fptr == NULL)
    {
      printf("Error!");   
      exit(1);     	  
    }
	char json_file[1000]="";
	
	const char  ob[10]="{";
	const char  cb[10]="}";
	const char  nl[10]="\n";
    
	strcat(json_file,ob);
	strcat(json_file,nl);
	//char x[20]=
	strcat(json_file,"  \"BMD\": ");
	strcat(json_file,ob);
	strcat(json_file,nl);
	strcat(json_file,"    \"Envelop\": ");
	strcat(json_file,ob);
	strcat(json_file,nl);
	strcat(json_file,"      \"MessageID\": \"");
	strcat(json_file,MessageID);
	strcat (json_file, "\",\n" );
	strcat(json_file,"      \"MessageType\": \"");
	strcat(json_file,MessageType);
	strcat (json_file, "\",\n" );
	strcat(json_file,"      \"Sender\": \"");
	strcat(json_file,Sender);
	strcat (json_file, "\",\n" );
	strcat(json_file,"      \"Destination\": \"");
	strcat(json_file,Destination);
	strcat (json_file, "\",\n" );
	strcat(json_file,"      \"CreationDateTime\": \"");
	strcat(json_file,CreationDateTime);
	strcat (json_file, "\",\n" );
	strcat(json_file,"      \"Signature\": \"");
	strcat(json_file,Signature);
	strcat (json_file, "\",\n" );
	strcat(json_file,"      \"ReferenceID\": \"");
	strcat(json_file,ReferenceID);
	strcat (json_file, "\",\n" );
	strcat (json_file, "    " );
	strcat (json_file, cb );
	strcat (json_file, ",\n" );
	strcat(json_file,"    \"Payload\": \"");
	strcat(json_file,Payload);
	strcat (json_file, "\",\n" );
	strcat (json_file, "  " );
	strcat (json_file, cb );
	strcat (json_file, "\n" );
	strcat (json_file, cb );
	strcat (json_file, "\n" );
	
	
    printf("%s",json_file);
	fprintf(fptr,"%s",json_file);
    fclose(fptr);
    return 0;
	
}