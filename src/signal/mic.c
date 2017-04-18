
    #include "mic.h"

    mics_obj * mics_construct_zero(const unsigned int nMics) {

        mics_obj * obj;

        obj = (mics_obj *) malloc(sizeof(mics_obj));

        obj->nMics = nMics;
        obj->mu = (float *) malloc(sizeof(float) * nMics * 3);
        memset(obj->mu, 0x00, sizeof(float) * nMics * 3);        
        obj->sigma = (float *) malloc(sizeof(float) * nMics * 9);
        memset(obj->sigma, 0x00, sizeof(float) * nMics * 9);        

        return obj;

    }

    void mics_destroy(mics_obj * obj) {

        free((void *) obj->mu);
        free((void *) obj->sigma);

    }