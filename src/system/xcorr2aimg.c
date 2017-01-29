    
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

    void xcorr2aimg_process(xcorr2aimg_obj * obj, const tdoas_obj * tdoas, const index_obj * index, const xcorrs_obj * xcorrs, aimg_obj * aimg) {

        unsigned int iPair;
        unsigned int iIndex;
        unsigned int iPoint;
        unsigned int tau;

        for (iPoint = 0; iPoint < aimg->aimgSize; iPoint++) {

            aimg->array[iPoint] = 0.0f;

        }

        for (iIndex = 0; iIndex < index->nIndexes; iIndex++) {

            iPoint = index->array[iIndex];

            for (iPair = 0; iPair < xcorrs->nSignals; iPair++) {               

                tau = tdoas->array[iPoint]->array[iPair];

                aimg->array[iPoint] += xcorrs->array[iPair]->array[tau];

            }

        }

    }