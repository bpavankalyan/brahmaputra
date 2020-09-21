#include <stdio.h>
#include <string.h>
#include <curl/curl.h>


 void *  email_send(void *to, void * file_path)
 {
  printf("Sending to %s\n", (char *) to);
  CURL *curl;
  CURLcode res = CURLE_OK;
  struct curl_slist *recipients = NULL;
  
  curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);
    curl_easy_setopt(curl, CURLOPT_USERNAME, "Testmailchenab1");
    curl_easy_setopt(curl, CURLOPT_PASSWORD, "Testmailchenab001@");//my real password
    curl_easy_setopt(curl, CURLOPT_URL, "smtp://smtp.gmail.com:587/");
    curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_ALL);
    curl_easy_setopt(curl, CURLOPT_MAIL_FROM, "Testmailchenab1@gmail.com");
    recipients = curl_slist_append(recipients, to);
    recipients = curl_slist_append(recipients, "Testmailchenab1@gmail.com");
    curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);
    FILE *fd = fopen(((char *) file_path ), "r");
    if(!fd){
      printf("no such file");
      return 0;
    }
    curl_easy_setopt(curl, CURLOPT_READDATA,fd);
    curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
    res = curl_easy_perform(curl);
    fclose(fd);
    if(res != CURLE_OK)
     { 
              fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
              return "NO";
     }
    /* Free the list of recipients */ 
    curl_slist_free_all(recipients);
    curl_easy_cleanup(curl);

  }
 return "YES";
}


/*
int main (){ 
    char * s= (char *) email_send("Testmailchenab1@gmail.com", "main.c");
    printf("%s\n",s);
}
*/