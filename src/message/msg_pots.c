    
    #include "msg_pots.h"

    msg_pots_obj * msg_pots_construct(const unsigned int nScans, const unsigned int nBands) {

        msg_pots_obj * obj;

        unsigned int iScan;
        unsigned int iBand;

        obj = (msg_pots_obj *) malloc(sizeof(msg_pots_obj));

        obj->nScans = nScans;
        obj->nBands = nBands;

        obj->samples = (float ***) malloc(sizeof(float **) * nScans);

        for (iScan = 0; iScan < obj->nScans; iScan++) {

            obj->samples[iScan] = (float **) malloc(sizeof(float *) * nBands);

            for (iBand = 0; iBand < obj->nBands; iBand++) {

                obj->samples[iScan][iBand] = (float *) malloc(sizeof(float) * 4);

            }

        }

        return obj;

    }

    void msg_pots_destroy(msg_pots_obj * obj) {

        unsigned int iScan;
        unsigned int iBand;

        for (iScan = 0; iScan < obj->nScans; iScan++) {

            for (iBand = 0; iBand < obj->nBands; iBand++) {

                free((void *) obj->samples[iScan][iBand]);

            }

            free((void *) obj->samples[iScan]);

        }

        free((void *) obj->samples);

        free((void *) obj);

    }