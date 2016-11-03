    #include "xcorr2aimg.h"

    xcorr2aimg_obj * xcorr2aimg_construct(const unsigned int frameSize, const unsigned int nMics, const unsigned int nPoints) {

        xcorr2aimg_obj * obj;

        obj = (xcorr2aimg_obj *) malloc(sizeof(xcorr2aimg_obj));

        obj->frameSize = frameSize;
        obj->nMics = nMics;
        obj->nPairs = (nMics-1) * nMics / 2;
        obj->nPoints = nPoints;

        return obj;

    }

    void xcorr2aimg_destroy(xcorr2aimg_obj * obj) {

        free((void *) obj);

    }

    int xcorr2aimg_process(const xcorr2aimg_obj * obj, const matrix_unsignedint * tdoas, const matrix_float * xcorrs, vector_float * aimg) {

        unsigned int iPair;
        unsigned int iPoint;

        for (iPoint = 0; iPoint < obj->nPoints; iPoint++) {

            aimg->array[iPoint] = 0.0f;

            for (iPair = 0; iPair < obj->nPairs; iPair++) {

                aimg->array[iPoint] += xcorrs->array[iPair][tdoas->array[iPoint][iPair]];

            }

        }

    }