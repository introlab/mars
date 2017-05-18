#ifndef __MARS_SINK_POTS_SOCKET
#define __MARS_SINK_POTS_SOCKET

    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>

    #include "../message/msg_pots.h"

    typedef struct snk_pots_socket_obj {

        struct sockaddr_in server;    
        char format;
        int id;
        char * message;

    } snk_pots_socket_obj;    

    typedef struct snk_pots_socket_cfg {

        char * ipAddress;
        char * portNumber;
        char format;

    } snk_pots_socket_cfg;

    snk_pots_socket_obj * snk_pots_socket_construct(const snk_pots_socket_cfg * cfg);

    void snk_pots_socket_destroy(snk_pots_socket_obj * obj);

    void snk_pots_socket_process(snk_pots_socket_obj * obj, msg_pots_obj * msg_pots);

    void snk_pots_socket_process_xml(snk_pots_socket_obj * obj, msg_pots_obj * msg_pots);

    void snk_pots_socket_process_json(snk_pots_socket_obj * obj, msg_pots_obj * msg_pots);

    snk_pots_socket_cfg * snk_pots_socket_cfg_construct(void);

    void snk_pots_socket_cfg_destroy(snk_pots_socket_cfg * cfg);

#endif