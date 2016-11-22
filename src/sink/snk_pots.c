 
    #include "snk_pots.h"

    snk_pots_obj * snk_pots_construct(const char * fileName, const char * format) {

        snk_pots_obj * obj;

        obj = (snk_pots_obj *) malloc(sizeof(snk_pots_obj));

        obj->fileName = (char *) malloc(sizeof(char) * (strlen(fileName) + 1));
        strcpy(obj->fileName, fileName);

        obj->format = (char *) malloc(sizeof(char) * (strlen(format) + 1));
        strcpy(obj->format, format);

        if (strcmp(format, "xml") == 0) {

            obj->fp = fopen(obj->fileName, "w");

        }
        else if (strcmp(format, "bin") == 0) {

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

    int snk_pots_process(snk_pots_obj * obj, msg_pots_obj * pots) {

        if (strcmp(obj->format,"xml") == 0) {
            
            snk_pots_process_xml(obj, pots);

        }
        if (strcmp(obj->format,"bin") == 0) {
            
            snk_pots_process_bin(obj, pots);

        }

    }

    int snk_pots_process_xml(snk_pots_obj * obj, msg_pots_obj * pots) {

        fprintf(obj->fp, "<frame id = \"%llu\">\n",pots->id);
        fprintf(obj->fp, "    <src>\n");
        fprintf(obj->fp, "        <x>%+1.3f</x>\n",pots->samples[0]);
        fprintf(obj->fp, "        <y>%+1.3f</y>\n",pots->samples[1]);
        fprintf(obj->fp, "        <z>%+1.3f</z>\n",pots->samples[2]);
        fprintf(obj->fp, "        <E>%+1.3f</E>\n",pots->samples[3]);
        fprintf(obj->fp, "    </src>\n");
        fprintf(obj->fp, "</frame>\n");

    }

    int snk_pots_process_bin(snk_pots_obj * obj, msg_pots_obj * pots) {

        fwrite(&(pots->id),sizeof(unsigned long long), 1, obj->fp);
        fwrite(&(pots->samples[0]), sizeof(float), 1, obj->fp);
        fwrite(&(pots->samples[1]), sizeof(float), 1, obj->fp);
        fwrite(&(pots->samples[2]), sizeof(float), 1, obj->fp);
        fwrite(&(pots->samples[3]), sizeof(float), 1, obj->fp);

    }