    
    #include "parser.h"

    void parser_extract_ipv4_ip(const char * str, char * ip) {

        int colon;
        char * rtnValue;

        for (colon = 0; colon < strlen(str); colon++) {
            
            if (str[colon] == ':') {
                break;
            }

        }

        memcpy(ip, str, colon * sizeof(char));
        ip[colon] = 0x00;

    }


    void parser_extract_ipv4_port(const char * str, char * port) {

        int colon;
        int dot;
        unsigned int rtnValue;

        for (colon = 0; colon < strlen(str); colon++) {

            if (str[colon] == ':') {
                break;
            }

        }

        for (dot = colon; dot < strlen(str); dot++) {

            if (str[dot] == '.') {
                break;
            }

        }

        memcpy(port, &(str[colon+1]), (dot-colon-1) * sizeof(char));
        port[dot-colon-1] = 0x00;

    }