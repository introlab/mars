#ifndef __MARS_GENERAL_PARSER
#define __MARS_GENERAL_PARSER

    #include <string.h>
    #include <stdio.h>
    #include <stdlib.h>

    void parser_extract_ipv4_ip(const char * str, char * ip);

    void parser_extract_ipv4_port(const char * str, char * port);

#endif