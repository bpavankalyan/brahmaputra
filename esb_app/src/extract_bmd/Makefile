

LIBXML_LIBS :=  -I/usr/include/libxml2 -lxml2
SQL_LIBS   :=  -I/usr/local/mysql/lib -lmysqlclient -lz

xml:  bmd_validate.c  bmd_extract.c ../database/select_active_route_id.c ../database/insert_esb_request.c  ../database/check_id_in_transform_config.c ../database/check_id_in_transport_config.c
	gcc  -Wall  -o xml main.c bmd_validate.c bmd_extract.c  \
	../database/select_active_route_id.c ../database/insert_esb_request.c \
	../database/check_id_in_transform_config.c ../database/check_id_in_transport_config.c  ${LIBXML_LIBS}  ${SQL_LIBS}




clean:
	rm *.o xml
