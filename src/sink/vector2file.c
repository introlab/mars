
    #include "vector2file.h"

    vector2file_obj * vector2file_construct(const char * fileName) {

        vector2file_obj * obj;

        obj = (vector2file_obj *) malloc(sizeof(vector2file_obj));

        obj->fileName = (char *) malloc(sizeof(char) * (strlen(fileName) + 1));
        strcpy(obj->fileName, fileName);

        obj->fp = fopen(obj->fileName, "wb");

        return obj;

    }

    void vector2file_destroy(vector2file_obj * obj) {

        free((void *) obj->fileName);
        fclose(obj->fp);

        free((void *) obj);

    }

    int vector2file_process_signedint(vector2file_obj * obj, const vector_signedint * vector) {

        printf("Not implemented yet.\n");
        exit(EXIT_FAILURE);
        
    }

    int vector2file_process_unsignedint(vector2file_obj * obj, const vector_unsignedint * vector) {

        printf("Not implemented yet.\n");
        exit(EXIT_FAILURE);
        
    }

    int vector2file_process_float(vector2file_obj * obj, const vector_float * vector) {      

        fwrite(vector->array, sizeof(float), vector->nElements, obj->fp);

    }
