XML_HANDLER = ../extract_bmd/bmd_extract.c ../extract_bmd/bmd.h  ../extract_bmd/bmd_validate.c
SQL_API     = ../database/insert_esb_request.c ../database/select_active_route_id.c ../database/check_id_in_transform_config.c ../database/check_id_in_transport_config.c
#SQL_API1    = ../database/update_esb_request.c  #../database/select_task_info.c ../database/fetch_transform_config_key_and_value.c ../database/fetch_transport_config_key_and_value.c
# ADAPTER_API = ../adapter/dynamic_lookup.c ../adapter/email.c ../adapter/http.c ../adapter/convert_to_json.c
XML_LIB     =   `xml2-config --cflags` `xml2-config --libs`
SQL_LIB     =  `mysql_config --cflags --libs`
esb: esb.c
	gcc esb.c ${XML_HANDLER} ${SQL_API} -o esb ${SQL_LIB} ${XML_LIB}



clean:
	rm esb

