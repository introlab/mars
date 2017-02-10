 
    #include "snk_pots_file.h"

    snk_pots_file_obj * snk_pots_file_construct(const snk_pots_file_cfg * cfg) {

        snk_pots_file_obj * obj;

        obj = (snk_pots_file_obj *) malloc(sizeof(snk_pots_file_obj));

        obj->fileName = (char *) malloc(sizeof(char) * (strlen(cfg->fileName) + 1));
        strcpy(obj->fileName, cfg->fileName);

        obj->format = cfg->format;

        if (obj->format == 'b') {

            obj->fp = fopen(obj->fileName, "w");

        }
        else if (obj->format == 'x') {

            obj->fp = fopen(obj->fileName, "wb");

        }
        else {

            printf("Invalid format\n");
            exit(EXIT_FAILURE);

        }        

        return obj;

    }

    void snk_pots_file_destroy(snk_pots_file_obj * obj) {

        free((void *) obj->fileName);
        fclose(obj->fp);

        free((void *) obj);

    }

    void snk_pots_file_process(snk_pots_file_obj * obj, msg_pots_obj * msg_pots) {

        if (obj->format == 'x') {
            
            snk_pots_file_process_xml(obj, msg_pots);

        }
        if (obj->format == 'b') {
            
            snk_pots_file_process_bin(obj, msg_pots);

        }

    }

    void snk_pots_file_process_xml(snk_pots_file_obj * obj, msg_pots_obj * msg_pots) {

        unsigned int iPot;

        fprintf(obj->fp, "<frame timestamp = \"%llu\">\n",msg_pots->timeStamp);
        
        for (iPot = 0; iPot < msg_pots->pots->nPots; iPot++) {
            
            fprintf(obj->fp, "    <src q = %u>\n",iPot);
            fprintf(obj->fp, "        <x>%+1.3f</x>\n",msg_pots->pots->array[iPot * 3 + 0]);
            fprintf(obj->fp, "        <y>%+1.3f</y>\n",msg_pots->pots->array[iPot * 3 + 1]);
            fprintf(obj->fp, "        <z>%+1.3f</z>\n",msg_pots->pots->array[iPot * 3 + 2]);
            fprintf(obj->fp, "        <E>%+1.3f</E>\n",msg_pots->pots->array[iPot * 3 + 3]);
            fprintf(obj->fp, "    </src>\n");

        }

        fprintf(obj->fp, "</frame>\n");

    }

    void snk_pots_file_process_bin(snk_pots_file_obj * obj, msg_pots_obj * msg_pots) {

        unsigned int iPot;

        fwrite(msg_pots->pots->array, sizeof(float), 4 * msg_pots->pots->nPots, obj->fp);

    }

    snk_pots_file_cfg * snk_pots_file_cfg_construct(void) {

        snk_pots_file_cfg * cfg;

        cfg = (snk_pots_file_cfg *) malloc(sizeof(snk_pots_file_cfg));

        cfg->fileName = (char *) NULL;

        return cfg;

    }

    void snk_pots_file_cfg_destroy(snk_pots_file_cfg * cfg) {

        if (cfg->fileName != NULL) {
            free((void *) cfg->fileName);
        }

        free((void *) cfg);

    }