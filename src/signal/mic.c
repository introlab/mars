
    #include "mic.h"

    mics_obj * mics_construct_zero(const unsigned int nMics) {

        mics_obj * obj;

        obj = (mics_obj *) malloc(sizeof(mics_obj));

        obj->nMics = nMics;
        obj->array = (float *) malloc(sizeof(float) * nMics * 3);
        memset(obj->array, 0x00, sizeof(float) * nMics * 3);

        return obj;

    }

    void mics_destroy(mics_obj * obj) {

        free((void *) obj->array);
        free((void *) obj);

    }
