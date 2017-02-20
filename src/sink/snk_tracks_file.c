 
    #include "snk_tracks_file.h"

    snk_tracks_file_obj * snk_tracks_file_construct(const snk_tracks_file_cfg * cfg) {

        snk_tracks_file_obj * obj;

        obj = (snk_tracks_file_obj *) malloc(sizeof(snk_tracks_file_obj));

        obj->fileName = (char *) malloc(sizeof(char) * (strlen(cfg->fileName) + 1));
        strcpy(obj->fileName, cfg->fileName);

        obj->format = cfg->format;

        if (obj->format == 'x') {

            obj->fp = fopen(obj->fileName, "w");

        }
        else if (obj->format == 'b') {

            obj->fp = fopen(obj->fileName, "wb");

        }
        else {

            printf("Invalid format\n");
            exit(EXIT_FAILURE);

        }        

        return obj;

    }

    void snk_tracks_file_destroy(snk_tracks_file_obj * obj) {

        free((void *) obj->fileName);
        fclose(obj->fp);

        free((void *) obj);

    }

    void snk_tracks_file_process(snk_tracks_file_obj * obj, msg_tracks_obj * msg_tracks) {

        if (obj->format == 'x') {
            
            snk_tracks_file_process_xml(obj, msg_tracks);

        }
        if (obj->format == 'b') {
            
            snk_tracks_file_process_bin(obj, msg_tracks);

        }

    }

    void snk_tracks_file_process_xml(snk_tracks_file_obj * obj, msg_tracks_obj * msg_tracks) {

        unsigned int iTrack;

        fprintf(obj->fp, "<frame timestamp = \"%llu\">\n",msg_tracks->timeStamp);
        
        for (iTrack = 0; iTrack < msg_tracks->tracks->nTracks; iTrack++) {
            
            if (msg_tracks->tracks->ids[iTrack] != 0) {

                fprintf(obj->fp, "    <src id = %llu>\n",msg_tracks->tracks->ids[iTrack]);
                fprintf(obj->fp, "        <x>%+1.3f</x>\n",msg_tracks->tracks->array[iTrack * 3 + 0]);
                fprintf(obj->fp, "        <y>%+1.3f</y>\n",msg_tracks->tracks->array[iTrack * 3 + 1]);
                fprintf(obj->fp, "        <z>%+1.3f</z>\n",msg_tracks->tracks->array[iTrack * 3 + 2]);
                fprintf(obj->fp, "    </src>\n");

            }

        }

        fprintf(obj->fp, "</frame>\n");

    }

    void snk_tracks_file_process_bin(snk_tracks_file_obj * obj, msg_tracks_obj * msg_tracks) {

        unsigned int iTrack;

        for (iTrack = 0; iTrack < msg_tracks->tracks->nTracks; iTrack++) {

            fwrite(&(msg_tracks->tracks->ids[iTrack]), sizeof(float), 1, obj->fp);
            fwrite(&(msg_tracks->tracks->array[iTrack * 3]), sizeof(float), 3, obj->fp);
            
        }

    }

    snk_tracks_file_cfg * snk_tracks_file_cfg_construct(void) {

        snk_tracks_file_cfg * cfg;

        cfg = (snk_tracks_file_cfg *) malloc(sizeof(snk_tracks_file_cfg));

        cfg->fileName = (char *) NULL;

        return cfg;

    }

    void snk_tracks_file_cfg_destroy(snk_tracks_file_cfg * cfg) {

        if (cfg->fileName != NULL) {
            free((void *) cfg->fileName);
        }

        free((void *) cfg);

    }