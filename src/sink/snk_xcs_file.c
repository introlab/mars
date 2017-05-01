    
    #include "snk_xcs_file.h"

    snk_xcs_file_obj * snk_xcs_file_construct(const snk_xcs_file_cfg * cfg) {

        snk_xcs_file_obj * obj;

        obj = (snk_xcs_file_obj *) malloc(sizeof(snk_xcs_file_obj));

        obj->fileName = (char *) malloc(sizeof(char) * (strlen(cfg->fileName) + 1));
        strcpy(obj->fileName, cfg->fileName);

        obj->format = cfg->format;

        if (obj->format == 'b') {

            obj->fp = fopen(obj->fileName, "w");

        }
        else {

            printf("Invalid format\n");
            exit(EXIT_FAILURE);

        }               

        return obj;

    }

    void snk_xcs_file_destroy(snk_xcs_file_obj * obj) {

        free((void *) obj->fileName);
        fclose(obj->fp);

        free((void *) obj);

    }

    void snk_xcs_file_process(snk_xcs_file_obj * obj, msg_xcs_obj * msg_xcs) {

        if (obj->format == 'b') {
            
            snk_xcs_file_process_bin(obj, msg_xcs);

        }

    }

    void snk_xcs_file_process_bin(snk_xcs_file_obj * obj, msg_xcs_obj * msg_xcs) {

        unsigned int iSignal;

        for (iSignal = 0; iSignal < msg_xcs->xcorrs->nSignals; iSignal++) {

            fwrite(msg_xcs->xcorrs->array[iSignal], sizeof(float), msg_xcs->xcorrs->frameSize, obj->fp);

        }

    }

    snk_xcs_file_cfg * snk_xcs_file_cfg_construct(void) {

        snk_xcs_file_cfg * cfg;

        cfg = (snk_xcs_file_cfg *) malloc(sizeof(snk_xcs_file_cfg));

        cfg->fileName = (char *) NULL;

        return cfg;

    }

    void snk_xcs_file_cfg_destroy(snk_xcs_file_cfg * cfg) {

        if (cfg->fileName != NULL) {
            free((void *) cfg->fileName);
        }

        free((void *) cfg);

    }