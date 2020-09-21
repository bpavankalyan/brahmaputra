
libxml =  -I/usr/include/libxml2 -lxml2
sa: email.c dynamic_lookup.c http.c  json_related.c adapter.h 
	gcc -o sa main.c email.c dynamic_lookup.c http.c  json_related.c ftp.c -lcurl adapter.h ${libxml}


clean:
	rm sa
