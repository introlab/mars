    
    #include "snk_tracks_socket.h"

    snk_tracks_socket_obj * snk_tracks_socket_construct(const snk_tracks_socket_cfg * cfg) {

        snk_tracks_socket_obj * obj;

        obj = (snk_tracks_socket_obj *) malloc(sizeof(snk_tracks_socket_obj));

        obj->server.sin_family = AF_INET;
        obj->server.sin_port = htons(atoi(cfg->portNumber));
        inet_aton(cfg->ipAddress, &(obj->server.sin_addr));

        obj->format = cfg->format;

        obj->message = (char *) malloc(sizeof(char) * 1024);

        if (obj->format == 'x') {

            obj->id = socket(AF_INET, SOCK_STREAM, 0);

            if ( (connect(obj->id, (struct sockaddr *) &(obj->server), sizeof(obj->server))) < 0 ) {

                printf("Cannot connect to server\n");
                exit(EXIT_FAILURE);

            }

        }
        else if (obj->format == 'j') {

            obj->id = socket(AF_INET, SOCK_STREAM, 0);

            if ( (connect(obj->id, (struct sockaddr *) &(obj->server), sizeof(obj->server))) < 0 ) {

                printf("Cannot connect to server\n");
                exit(EXIT_FAILURE);

            }

        }
        else {

            printf("Invalid format\n");
            exit(EXIT_FAILURE);

        }        

        return obj;

    }

    void snk_tracks_socket_destroy(snk_tracks_socket_obj * obj) {

        free((void *) obj->message);
        free((void *) obj);

    }

    void snk_tracks_socket_process(snk_tracks_socket_obj * obj, msg_tracks_obj * msg_tracks) {

        if (obj->format == 'x') {
            snk_tracks_socket_process_xml(obj, msg_tracks);
        }
        if (obj->format == 'j') {
            snk_tracks_socket_process_json(obj, msg_tracks);
        }

    }

    void snk_tracks_socket_process_xml(snk_tracks_socket_obj * obj, msg_tracks_obj * msg_tracks) {

        unsigned int iTrack;

        sprintf(obj->message, "<frame timestamp = \"%llu\">\n",msg_tracks->timeStamp);
        
        for (iTrack = 0; iTrack < msg_tracks->tracks->nTracks; iTrack++) {
            
            if (msg_tracks->tracks->ids[iTrack] != 0) {

                sprintf(obj->message, "%s    <src id = \"%llu\">\n",obj->message,msg_tracks->tracks->ids[iTrack]);
                sprintf(obj->message, "%s        <x>%+1.3f</x>\n",obj->message,msg_tracks->tracks->array[iTrack * 3 + 0]);
                sprintf(obj->message, "%s        <y>%+1.3f</y>\n",obj->message,msg_tracks->tracks->array[iTrack * 3 + 1]);
                sprintf(obj->message, "%s        <z>%+1.3f</z>\n",obj->message,msg_tracks->tracks->array[iTrack * 3 + 2]);
                sprintf(obj->message, "%s    </src>\n",obj->message);

            }

        }

        sprintf(obj->message, "%s</frame>\n", obj->message);     

        if (send(obj->id, obj->message, strlen(obj->message), 0) < 0) {
            printf("Could not send message.\n");
            exit(EXIT_FAILURE);
        }

    }

    void snk_tracks_socket_process_json(snk_tracks_socket_obj * obj, msg_tracks_obj * msg_tracks) {

        unsigned int iTrack;
        unsigned int nElements;

        sprintf(obj->message, "{\n\"frame\": {\n");
        sprintf(obj->message, "%s   \"timestamp\": %llu",obj->message, msg_tracks->timeStamp);

        nElements = 0;

        for (iTrack = 0; iTrack < msg_tracks->tracks->nTracks; iTrack++) {

            if (msg_tracks->tracks->ids[iTrack] != 0) {

                nElements++;
                
                if (nElements > 1) {
                    sprintf(obj->message,"%s,\n",obj->message);
                }
                else {
                    sprintf(obj->message, "%s,\n   \"src\": [\n",obj->message);
                }

                sprintf(obj->message, "%s       { \"id\": %llu, \"x\": %1.3f, \"y\": %1.3f, \"z\": %1.3f }", 
                        obj->message,
                        msg_tracks->tracks->ids[iTrack],
                        msg_tracks->tracks->array[iTrack * 3 + 0],
                        msg_tracks->tracks->array[iTrack * 3 + 1],
                        msg_tracks->tracks->array[iTrack * 3 + 2]);

            }

        }

        if (nElements > 0) {
            sprintf(obj->message, "%s\n   ]\n", obj->message);    
        }
        else {
            sprintf(obj->message, "%s\n", obj->message);       
        }

        sprintf(obj->message, "%s}\n}\n", obj->message);
        
        if (send(obj->id, obj->message, strlen(obj->message), 0) < 0) {
            printf("Could not send message.\n");
            exit(EXIT_FAILURE);
        }

    }

    snk_tracks_socket_cfg * snk_tracks_socket_cfg_construct(void) {

        snk_tracks_socket_cfg * cfg;

        cfg = (snk_tracks_socket_cfg *) malloc(sizeof(snk_tracks_socket_cfg));

        cfg->ipAddress = (char *) NULL;
        cfg->portNumber = (char *) NULL;
        cfg->format = 0x00;

        return cfg;

    }

    void snk_tracks_socket_cfg_destroy(snk_tracks_socket_cfg * cfg) {

        if (cfg->ipAddress != NULL) {
            free((void *) cfg->ipAddress);
        }

        if (cfg->portNumber != NULL) {
            free((void *) cfg->portNumber);
        }

        free((void *) cfg);

    }
