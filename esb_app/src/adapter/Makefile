
libxml =  -I/usr/include/libxml2 -lxml2
ADAPTER_HANDLER = dynamic_lookup.c http.c  email.c  ftp.c json_related.c
INCLUDE = `mysql_config --cflags --libs` `xml2-config --cflags` `xml2-config --libs` -lcurl

sa: email.c dynamic_lookup.c http.c  json_related.c adapter.h 
#	gcc -o sa main.c email.c dynamic_lookup.c http.c  json_related.c ftp.c -lcurl adapter.h ${libxml}
	gcc  ${ADAPTER_HANDLER} test_adapter.c -o sa  ${INCLUDE} ../test/munit.c


clean:
	rm sa
