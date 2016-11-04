    #include "msg_hops.h"

    msg_hops_obj * msg_hops_construct(const unsigned int hopSize, const unsigned int nMics) {

        msg_hops_obj * obj;
        unsigned int iMic;

        obj = (msg_hops_obj *) malloc(sizeof(msg_hops_obj));

        obj->hopSize = hopSize;
        obj->nMics = nMics;

        obj->samples = (float **) malloc(sizeof(float *) * nMics);

        for (iMic = 0; iMic < nMics; iMic++) {

            obj->samples[iMic] = malloc(sizeof(float) * hopSize);

        }

        return obj;

    }

    void msg_hops_destroy(msg_hops_obj * obj) {

        unsigned int iMic;

        for (iMic = 0; iMic < obj->nMics; iMic++) {

            free((void *) obj->samples[iMic]);

        }

        free((void *) obj->samples);

        free((void *) obj);

    }