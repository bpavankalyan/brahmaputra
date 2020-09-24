DB_ACCESS = ../database/select_active_route_id.c ../database/check_id_in_transport_config.c  \
          ../database/check_id_in_transform_config.c   ../database/insert_esb_request.c 

DB_ACCESS1 = ../database/fetch_transform_config_key_and_value.c  \
          ../database/fetch_transport_config_key_and_value.c  ../database/update_esb_request.c \
          ../database/check_new_request.c

XML_HANDLER = ../extract_bmd/bmd_extract.c ../extract_bmd/bmd_validate.c
ESB_HANDLER = ../esb/esb.c ../esb/cleanup.c 
ADAPTER_HANDLER = ../adapter/dynamic_lookup.c ../adapter/http.c ../adapter/email.c ../adapter/ftp.c\
                ../adapter/json_related.c

INCLUDE = `mysql_config --cflags --libs` `xml2-config --cflags` `xml2-config --libs` -lcurl
bmd:  ${ADAPTER_HANDLER}
#	gcc  ${XML_HANDLER} ${DB_ACCESS1} ${DB_ACCESS} test_bmd.c -o bmd  ${ESB_HANDLER} ${INCLUDE}  munit.c
#	gcc  ${XML_HANDLER} ${DB_ACCESS1} ${DB_ACCESS} test_db_access.c -o bmd  ${ESB_HANDLER} ${INCLUDE}  munit.c
	gcc    ${ADAPTER_HANDLER} test_adapter.c -o bmd  ${INCLUDE}  munit.c





clean :
	rm bmd
