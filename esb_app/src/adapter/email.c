#include <stdio.h>
#include <string.h>
#include <curl/curl.h>


int sendMail(char *to, char *json_file) { 
  printf("Sending to %s\n", to);
  CURL *curl;
  CURLcode res = CURLE_OK;
  struct curl_slist *recipients = NULL;
  
  curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);
    curl_easy_setopt(curl, CURLOPT_USERNAME, "riyatoteja1998@gmail.com");
    curl_easy_setopt(curl, CURLOPT_PASSWORD, "*****************");//my real password
    curl_easy_setopt(curl, CURLOPT_URL, "smtp://smtp.gmail.com:587/");
    curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_ALL);
    curl_easy_setopt(curl, CURLOPT_MAIL_FROM, "riyatoteja1998@gmail.com");
    recipients = curl_slist_append(recipients, to);
    recipients = curl_slist_append(recipients, "riyatoteja1998@gmail.com");
    curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);
    char* filepath=json_file;
    FILE *fd = fopen(filepath, "r");
    if(!fd){printf("no such file");}
    curl_easy_setopt(curl, CURLOPT_READDATA,fd);
    curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
    res = curl_easy_perform(curl);
    if(res != CURLE_OK)
     { 
              fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
              return -1;
     }
    /* Free the list of recipients */ 
    curl_slist_free_all(recipients);
    curl_easy_cleanup(curl);

  }
 return 0;
}

/*
int main (){ 
    int i=sendMail("riyatoteja1998@gmail.com", "../../payload.json");
}*/
