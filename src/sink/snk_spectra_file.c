 
    #include "snk_spectra_file.h"

    snk_spectra_file_obj * snk_spectra_file_construct(const snk_spectra_file_cfg * cfg) {

        snk_spectra_file_obj * obj;

        obj = (snk_spectra_file_obj *) malloc(sizeof(snk_spectra_file_obj));

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

    void snk_spectra_file_destroy(snk_spectra_file_obj * obj) {

        free((void *) obj->fileName);
        fclose(obj->fp);

        free((void *) obj);

    }

    void snk_spectra_file_process(snk_spectra_file_obj * obj, msg_spectra_obj * msg_spectra) {

        if (obj->format == 'b') {
            
            snk_spectra_file_process_bin(obj, msg_spectra);

        }

    }

    void snk_spectra_file_process_bin(snk_spectra_file_obj * obj, msg_spectra_obj * msg_spectra) {

        unsigned int iSignal;

        for (iSignal = 0; iSignal < msg_spectra->freqs->nSignals; iSignal++) {

            fwrite(msg_spectra->freqs->array[iSignal], sizeof(float), 2 * msg_spectra->freqs->halfFrameSize, obj->fp);

        }

    }

    snk_spectra_file_cfg * snk_spectra_file_cfg_construct(void) {

        snk_spectra_file_cfg * cfg;

        cfg = (snk_spectra_file_cfg *) malloc(sizeof(snk_spectra_file_cfg));

        cfg->fileName = (char *) NULL;

        return cfg;

    }

    void snk_spectra_file_cfg_destroy(snk_spectra_file_cfg * cfg) {

        if (cfg->fileName != NULL) {
            free((void *) cfg->fileName);
        }

        free((void *) cfg);

    }