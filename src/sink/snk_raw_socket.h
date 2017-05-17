#ifndef __MARS_SINK_RAW_SOCKET
#define __MARS_SINK_RAW_SOCKET

    #include <stdlib.h>
    #include <string.h>
    #include <stdio.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>

    #include "../message/msg_hops.h"
    #include "../utils/pcm.h"

    typedef struct snk_raw_socket_obj {
    
        unsigned long long timeStamp;

        unsigned int hopSize;
        unsigned int nChannels;
        unsigned int nBits;
        unsigned int messageSize;

        struct sockaddr_in * servers;  
        char format;
        int * ids;
        char * message;        

    } snk_raw_socket_obj;

    typedef struct snk_raw_socket_cfg {

        unsigned int hopSize;
        unsigned int nChannels;
        unsigned int nBits;

        char * ipAddress;
        char * portNumber;
        char format;        

    } snk_raw_socket_cfg;

    snk_raw_socket_obj * snk_raw_socket_construct(const snk_raw_socket_cfg * cfg);

    void snk_raw_socket_destroy(const snk_raw_socket_obj * obj);

    int snk_raw_socket_process(snk_raw_socket_obj * obj, msg_hops_obj * msg_hops);

    snk_raw_socket_cfg * snk_raw_socket_cfg_construct(void);

    void snk_raw_socket_cfg_destroy(snk_raw_socket_cfg * cfg);

#endif