    
    #include "xcorr2aimg.h"

    xcorr2aimg_obj * xcorr2aimg_construct_zero(const unsigned int aimgSize) {

        xcorr2aimg_obj * obj;

        obj = (xcorr2aimg_obj *) malloc(sizeof(xcorr2aimg_obj));

        obj->aimgSize = aimgSize;

        return obj;

    }

    void xcorr2aimg_destroy(xcorr2aimg_obj * obj) {

        free((void *) obj);

    }

    void xcorr2aimg_process(xcorr2aimg_obj * obj, const tdoas_obj * tdoas, const indexes_obj * indexes, const unsigned int iCoarse, const xcorrs_obj * xcorrs, aimg_obj * aimg) {

        unsigned int iPair;
        unsigned int iFine;
        unsigned int iPoint;
        unsigned int tau;

        memset(aimg->array, 0x00, sizeof(float) * aimg->aimgSize);

        for (iFine = 0; iFine < indexes->count[iCoarse]; iFine++) {

            iPoint = indexes->array[iCoarse * indexes->nFines + iFine];

            for (iPair = 0; iPair < xcorrs->nSignals; iPair++) {               

                tau = tdoas->array[iPoint * tdoas->nPairs + iPair];

                aimg->array[iPoint] += xcorrs->array[iPair * xcorrs->frameSize + tau];

            }

        }

    }