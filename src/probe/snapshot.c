
    #include "snapshot.h"

    snapshot_obj * snapshot_construct(const char * fileName) {

        snapshot_obj * obj;

        obj = (snapshot_obj *) malloc(sizeof(snapshot_obj));

        obj->fileName = (char *) malloc(sizeof(char) * (strlen(fileName)+1));
        strcpy(obj->fileName, fileName);
        obj->fp = fopen(obj->fileName, "wb");

        return obj;

    }

    void snapshot_destroy(snapshot_obj * obj) {

        fclose(obj->fp);
        free((void *) obj->fileName);

    }

    int snapshot_vector_signedint(snapshot_obj * obj, const vector_signedint * vector) {

        fwrite(vector->array, sizeof(signed int), vector->nElements, obj->fp);

    }

    int snapshot_vector_unsignedint(snapshot_obj * obj, const vector_unsignedint * vector) {

        fwrite(vector->array, sizeof(unsigned int), vector->nElements, obj->fp);

    }

    int snapshot_vector_float(snapshot_obj * obj, const vector_float * vector) {

        fwrite(vector->array, sizeof(float), vector->nElements, obj->fp);

    }