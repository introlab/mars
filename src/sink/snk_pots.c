 
    #include "snk_pots.h"

    snk_pots_obj * snk_pots_construct(const snk_pots_cfg * cfg) {

        snk_pots_obj * obj;

        obj = (snk_pots_obj *) malloc(sizeof(snk_pots_obj));

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

    void snk_pots_destroy(snk_pots_obj * obj) {

        free((void *) obj->fileName);
        free((void *) obj->format);
        fclose(obj->fp);

        free((void *) obj);

    }

    void snk_pots_process(snk_pots_obj * obj, msg_pots_obj * msg_pots) {

        if (strcmp(obj->format,"xml") == 0) {
            
            snk_pots_process_xml(obj, msg_pots);

        }
        if (strcmp(obj->format,"bin") == 0) {
            
            snk_pots_process_bin(obj, msg_pots);

        }

    }

    void snk_pots_process_xml(snk_pots_obj * obj, msg_pots_obj * msg_pots) {

        unsigned int iPot;

        fprintf(obj->fp, "<frame timestamp = \"%llu\">\n",msg_pots->timeStamp);
        
        for (iPot = 0; iPot < msg_pots->pots->nSignals; iPot++) {
            
            fprintf(obj->fp, "    <src q = %u>\n",iPot);
            fprintf(obj->fp, "        <x>%+1.3f</x>\n",msg_pots->pots->array[iPot]->coord->x);
            fprintf(obj->fp, "        <y>%+1.3f</y>\n",msg_pots->pots->array[iPot]->coord->y);
            fprintf(obj->fp, "        <z>%+1.3f</z>\n",msg_pots->pots->array[iPot]->coord->z);
            fprintf(obj->fp, "        <E>%+1.3f</E>\n",msg_pots->pots->array[iPot]->E);
            fprintf(obj->fp, "    </src>\n");

        }

        fprintf(obj->fp, "</frame>\n");

    }

    void snk_pots_process_bin(snk_pots_obj * obj, msg_pots_obj * msg_pots) {

        unsigned int iPot;

        for (iPot = 0; iPot < msg_pots->pots->nSignals; iPot++) {

            fwrite(&(msg_pots->pots->array[iPot]->coord->x), sizeof(float), 1, obj->fp);
            fwrite(&(msg_pots->pots->array[iPot]->coord->y), sizeof(float), 1, obj->fp);
            fwrite(&(msg_pots->pots->array[iPot]->coord->z), sizeof(float), 1, obj->fp);
            fwrite(&(msg_pots->pots->array[iPot]->E), sizeof(float), 1, obj->fp);

        }

    }

    snk_pots_cfg * snk_pots_cfg_construct(void) {

        snk_pots_cfg * cfg;

        cfg = (snk_pots_cfg *) malloc(sizeof(snk_pots_cfg));

        cfg->fileName = (char *) NULL;
        cfg->format = (char *) NULL;;

        return cfg;

    }

    void snk_pots_cfg_destroy(snk_pots_cfg * cfg) {

        if (cfg->fileName != NULL) {
            free((void *) cfg->fileName);
        }

        if (cfg->format != NULL) {
            free((void *) cfg->format);
        }

    }