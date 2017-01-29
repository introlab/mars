 
    #include "snk_tracks.h"

    snk_tracks_obj * snk_tracks_construct(const snk_tracks_cfg * cfg) {

        snk_tracks_obj * obj;

        obj = (snk_tracks_obj *) malloc(sizeof(snk_tracks_obj));

        obj->fileName = (char *) malloc(sizeof(char) * (strlen(cfg->fileName) + 1));
        strcpy(obj->fileName, cfg->fileName);

        obj->format = (char *) malloc(sizeof(char) * (strlen(cfg->format) + 1));
        strcpy(obj->format, cfg->format);

        if (strcmp(obj->format, "xml") == 0) {

            obj->fp = fopen(obj->fileName, "w");

        }
        else if (strcmp(obj->format, "bin") == 0) {

            obj->fp = fopen(obj->fileName, "wb");

        }
        else {

            printf("Invalid format\n");
            exit(EXIT_FAILURE);

        }        

        return obj;

    }

    void snk_tracks_destroy(snk_tracks_obj * obj) {

        free((void *) obj->fileName);
        free((void *) obj->format);
        fclose(obj->fp);

        free((void *) obj);

    }

    void snk_tracks_process(snk_tracks_obj * obj, msg_tracks_obj * msg_tracks) {

        if (strcmp(obj->format,"xml") == 0) {
            
            snk_tracks_process_xml(obj, msg_tracks);

        }
        if (strcmp(obj->format,"bin") == 0) {
            
            snk_tracks_process_bin(obj, msg_tracks);

        }

    }

    void snk_tracks_process_xml(snk_tracks_obj * obj, msg_tracks_obj * msg_tracks) {

        printf("Not available yet\n");
        exit(EXIT_FAILURE);

    }

    void snk_tracks_process_bin(snk_tracks_obj * obj, msg_tracks_obj * msg_tracks) {

        unsigned int iTrack;
        float tmpId;

        for (iTrack = 0; iTrack < msg_tracks->tracks->nSignals; iTrack++) {

            tmpId = (float) (msg_tracks->tracks->array[iTrack]->id);
            fwrite(&(tmpId), sizeof(float), 1, obj->fp);
            fwrite(&(msg_tracks->tracks->array[iTrack]->coord->x), sizeof(float), 1, obj->fp);
            fwrite(&(msg_tracks->tracks->array[iTrack]->coord->y), sizeof(float), 1, obj->fp);
            fwrite(&(msg_tracks->tracks->array[iTrack]->coord->z), sizeof(float), 1, obj->fp);
            
        }

    }

    snk_tracks_cfg * snk_tracks_cfg_construct(void) {

        snk_tracks_cfg * cfg;

        cfg = (snk_tracks_cfg *) malloc(sizeof(snk_tracks_cfg));

        cfg->fileName = (char *) NULL;
        cfg->format = (char *) NULL;

        return cfg;

    }

    void snk_tracks_cfg_destroy(snk_tracks_cfg * cfg) {

        if (cfg->fileName != NULL) {
            free((void *) cfg->fileName);
        }

        if (cfg->format != NULL) {
            free((void *) cfg->format);
        }

        free((void *) cfg);

    }