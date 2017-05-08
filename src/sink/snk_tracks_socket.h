#ifndef __MARS_SINK_TRACKS_SOCKET
#define __MARS_SINK_TRACKS_SOCKET

    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>

    #include "../message/msg_tracks.h"

    typedef struct snk_tracks_socket_obj {

        struct sockaddr_in server;    
        char format;
        int id;
        char * message;

    } snk_tracks_socket_obj;    

    typedef struct snk_tracks_socket_cfg {

        char * ipAddress;
        char * portNumber;
        char format;

    } snk_tracks_socket_cfg;

    snk_tracks_socket_obj * snk_tracks_socket_construct(const snk_tracks_socket_cfg * cfg);

    void snk_tracks_socket_destroy(snk_tracks_socket_obj * obj);

    void snk_tracks_socket_process(snk_tracks_socket_obj * obj, msg_tracks_obj * msg_tracks);

    void snk_tracks_socket_process_xml(snk_tracks_socket_obj * obj, msg_tracks_obj * msg_tracks);

    void snk_tracks_socket_process_json(snk_tracks_socket_obj * obj, msg_tracks_obj * msg_tracks);

    snk_tracks_socket_cfg * snk_tracks_socket_cfg_construct(void);

    void snk_tracks_socket_cfg_destroy(snk_tracks_socket_cfg * cfg);

#endif