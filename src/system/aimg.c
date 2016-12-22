    #include "aimg.h"

    #include <stdio.h>

    aimg_obj * aimg_construct(const unsigned int frameSize, const unsigned int nMics, const unsigned int nPoints) {

        aimg_obj * obj;

        obj = (aimg_obj *) malloc(sizeof(aimg_obj));

        obj->frameSize = frameSize;
        obj->nMics = nMics;
        obj->nPairs = (nMics-1) * nMics / 2;
        obj->nPoints = nPoints;

        return obj;

    }

    void aimg_destroy(aimg_obj * obj) {

        free((void *) obj);

    }

    int aimg_process(const aimg_obj * obj, const matrix_unsignedint * tdoas, const matrix_unsignedint * invmap, const unsigned int iPointCoarse, const vector_float ** xcorrs, vector_float * aimg) {

        unsigned int iIndex;
        unsigned int iPair;
        unsigned int iPoint;
        unsigned int iSample;

        for (iPoint = 0; iPoint < obj->nPoints; iPoint++) {
            aimg->array[iPoint] = 0.0f;
        }

        for (iIndex = 0; iIndex < invmap->nCols; iIndex++) {

            if (invmap->array[iPointCoarse][iIndex] == 0) {
                break;
            }

            iPoint = invmap->array[iPointCoarse][iIndex] - 1;

            for (iPair = 0; iPair < obj->nPairs; iPair++) {

                aimg->array[iPoint] += xcorrs[iPair]->array[tdoas->array[iPoint][iPair]];

            }

        }

        return 0;

    }