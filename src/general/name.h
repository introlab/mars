#ifndef __MARS_GENERAL_NAME
#define __MARS_GENERAL_NAME

    #include <regex.h>

    int name_check_file_raw(const char * str);

    int name_check_file_wav(const char * str);

    int name_check_file_cfg(const char * str);

    int name_check_file_spectrabin(const char * str);

    int name_check_file_xcsbin(const char * str);

    int name_check_file_potbin(const char * str);

    int name_check_file_potxml(const char * str);

    int name_check_file_trackbin(const char * str);

    int name_check_file_trackxml(const char * str);

    int name_check_ipv4_raw(const char * str);

    int name_check_ipv4_potxml(const char * str);

    int name_check_ipv4_potjson(const char * str);

    int name_check_ipv4_trackxml(const char * str);

    int name_check_ipv4_trackjson(const char * str);

    int name_check_hw(const char * str);

    int name_check_plughw(const char * str);

#endif