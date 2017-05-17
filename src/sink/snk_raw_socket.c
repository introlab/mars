    
    #include "snk_raw_socket.h"

    snk_raw_socket_obj * snk_raw_socket_construct(const snk_raw_socket_cfg * cfg) {

        snk_raw_socket_obj * obj;
        unsigned int iChannel;

        obj = (snk_raw_socket_obj *) malloc(sizeof(snk_raw_socket_obj));

        obj->hopSize = cfg->hopSize;
        obj->nChannels = cfg->nChannels;
        obj->nBits = cfg->nBits;
        obj->messageSize = (obj->nBits/8) * obj->hopSize;

        obj->servers = (struct sockaddr_in *) malloc(sizeof(struct sockaddr_in) * cfg->nChannels);

        for (iChannel = 0; iChannel < obj->nChannels; iChannel++) {

            obj->servers[iChannel].sin_family = AF_INET;
            obj->servers[iChannel].sin_port = htons(atoi(cfg->portNumber) + 1 + iChannel);
            inet_aton(cfg->ipAddress, &(obj->servers[iChannel].sin_addr));

        }
        
        obj->format = cfg->format;

        obj->ids = (int *) malloc(sizeof(int) * cfg->nChannels);

        if (obj->format == 'b') {

            obj->message = (char *) malloc(sizeof(char) * obj->messageSize);

            for (iChannel = 0; iChannel < obj->nChannels; iChannel++) {

                obj->ids[iChannel] = socket(AF_INET, SOCK_STREAM, 0);

                if ( (connect(obj->ids[iChannel], (struct sockaddr *) &(obj->servers[iChannel]), sizeof(obj->servers[iChannel]))) < 0 ) {

                    printf("Cannot connect to server\n");
                    exit(EXIT_FAILURE);

                }

            }

        }
        else {

            printf("Invalid format\n");
            exit(EXIT_FAILURE);

        }        

        return obj;

    }

    void snk_raw_socket_destroy(const snk_raw_socket_obj * obj) {

        free((void *) obj->message);
        free((void *) obj);

    }

    int snk_raw_socket_process(snk_raw_socket_obj * obj, msg_hops_obj * msg_hops) {

        unsigned int iSample;
        unsigned int iChannel;
        signed char sampleChar;
        signed short sampleShort;
        signed int sampleInt;
        float sample;

        for (iChannel = 0; iChannel < obj->nChannels; iChannel++) {

            for (iSample = 0; iSample < obj->hopSize; iSample++) {

                sample = msg_hops->hops->array[iChannel][iSample];

                switch (obj->nBits) {
                    
                    case 16:

                        sampleShort = pcm_normalized2signed16bits(sample);
                        ((signed short *) (obj->message))[iSample] = sampleShort;
                    
                    break;

                    case 32:

                        sampleInt = pcm_normalized2signed32bits(sample);
                        ((signed int *) (obj->message))[iSample] = sampleInt;               

                    break;

                }

            }

            if (send(obj->ids[iChannel], obj->message, obj->messageSize, 0) < 0) {
                printf("Could not send message.\n");
                exit(EXIT_FAILURE);
            }        

        }

        return 0;

    }

    snk_raw_socket_cfg * snk_raw_socket_cfg_construct(void) {

        snk_raw_socket_cfg * cfg;

        cfg = (snk_raw_socket_cfg *) malloc(sizeof(snk_raw_socket_cfg));

        cfg->ipAddress = (char *) NULL;
        cfg->portNumber = (char *) NULL;
        cfg->format = 0x00;

        return cfg;

    }

    void snk_raw_socket_cfg_destroy(snk_raw_socket_cfg * cfg) {

        if (cfg->ipAddress != NULL) {
            free((void *) cfg->ipAddress);
        }

        if (cfg->portNumber != NULL) {
            free((void *) cfg->portNumber);
        }

        free((void *) cfg);

    }