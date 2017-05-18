    
    #include "snk_pots_socket.h"

    snk_pots_socket_obj * snk_pots_socket_construct(const snk_pots_socket_cfg * cfg) {

       snk_pots_socket_obj * obj;

        obj = (snk_pots_socket_obj *) malloc(sizeof(snk_pots_socket_obj));

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

    void snk_pots_socket_destroy(snk_pots_socket_obj * obj) {

        free((void *) obj->message);
        free((void *) obj);

    }

    void snk_pots_socket_process(snk_pots_socket_obj * obj, msg_pots_obj * msg_pots) {

        if (obj->format == 'x') {
            snk_pots_socket_process_xml(obj, msg_pots);
        }
        if (obj->format == 'j') {
            snk_pots_socket_process_json(obj, msg_pots);
        }

    }

    void snk_pots_socket_process_xml(snk_pots_socket_obj * obj, msg_pots_obj * msg_pots) {

        unsigned int iPot;

        sprintf(obj->message, "<frame timestamp = \"%llu\">\n",msg_pots->timeStamp);
        
        for (iPot = 0; iPot < msg_pots->pots->nPots; iPot++) {

            sprintf(obj->message, "%s    <src index = \"%u\">\n",obj->message,iPot);
            sprintf(obj->message, "%s        <x>%+1.3f</x>\n",obj->message,msg_pots->pots->array[iPot * 4 + 0]);
            sprintf(obj->message, "%s        <y>%+1.3f</y>\n",obj->message,msg_pots->pots->array[iPot * 4 + 1]);
            sprintf(obj->message, "%s        <z>%+1.3f</z>\n",obj->message,msg_pots->pots->array[iPot * 4 + 2]);
            sprintf(obj->message, "%s        <e>%+1.3f</e>\n",obj->message,msg_pots->pots->array[iPot * 4 + 3]);
            sprintf(obj->message, "%s    </src>\n",obj->message);

        }

        sprintf(obj->message, "%s</frame>\n", obj->message);     

        if (send(obj->id, obj->message, strlen(obj->message), 0) < 0) {
            printf("Could not send message.\n");
            exit(EXIT_FAILURE);
        }

    }

    void snk_pots_socket_process_json(snk_pots_socket_obj * obj, msg_pots_obj * msg_pots) {

        unsigned int iPot;

        sprintf(obj->message, "{\n\"frame\": {\n");
        sprintf(obj->message, "%s   \"timestamp\": %llu",obj->message, msg_pots->timeStamp);

        for (iPot = 0; iPot < msg_pots->pots->nPots; iPot++) {
                
            if (iPot > 0) {
                sprintf(obj->message,"%s,\n",obj->message);
            }
            else {
                sprintf(obj->message, "%s,\n   \"src\": [\n",obj->message);
            }

            sprintf(obj->message, "%s       { \"x\": %1.3f, \"y\": %1.3f, \"z\": %1.3f, \"e\": %1.3f }", 
                    obj->message,
                    msg_pots->pots->array[iPot * 4 + 0],
                    msg_pots->pots->array[iPot * 4 + 1],
                    msg_pots->pots->array[iPot * 4 + 2],
                    msg_pots->pots->array[iPot * 4 + 3]);

        }

        if (msg_pots->pots->nPots > 0) {
            sprintf(obj->message, "%s\n   ]\n", obj->message);    
        }
        else {
            sprintf(obj->message, "%s\n", obj->message);       
        }

        sprintf(obj->message, "%s}\n}$", obj->message);
        
        if (send(obj->id, obj->message, strlen(obj->message), 0) < 0) {
            printf("Could not send message.\n");
            exit(EXIT_FAILURE);
        }

    }

    snk_pots_socket_cfg * snk_pots_socket_cfg_construct(void) {

        snk_pots_socket_cfg * cfg;

        cfg = (snk_pots_socket_cfg *) malloc(sizeof(snk_pots_socket_cfg));

        cfg->ipAddress = (char *) NULL;
        cfg->portNumber = (char *) NULL;
        cfg->format = 0x00;

        return cfg;

    }

    void snk_pots_socket_cfg_destroy(snk_pots_socket_cfg * cfg) {


        if (cfg->ipAddress != NULL) {
            free((void *) cfg->ipAddress);
        }

        if (cfg->portNumber != NULL) {
            free((void *) cfg->portNumber);
        }

        free((void *) cfg);

    }