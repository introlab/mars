    
    #include "xcorr2xcorr.h"

    xcorr2xcorr_obj * xcorr2xcorr_construct_zero(const unsigned int frameSize) {

        xcorr2xcorr_obj * obj;

        obj = (xcorr2xcorr_obj *) malloc(sizeof(xcorr2xcorr_obj));

        obj->frameSize = frameSize;

        return obj;

    }

    void xcorr2xcorr_destroy(xcorr2xcorr_obj * obj) {

        free((void *) obj);

    }

    void xcorr2xcorr_process_copy(xcorr2xcorr_obj * obj, const xcorrs_obj * xcorrsSrc, xcorrs_obj * xcorrsDest) {

        unsigned int iSignal;

        for (iSignal = 0; iSignal < xcorrsSrc->nSignals; iSignal++) {

            memcpy(xcorrsDest->array[iSignal],xcorrsSrc->array[iSignal],obj->frameSize * sizeof(float));

        }

    }

    void xcorr2xcorr_process_max(xcorr2xcorr_obj * obj, const xcorrs_obj * xcorrs, const tdoas_obj * tdoas, const deltas_obj * deltas, xcorrs_obj * xcorrsMax) {

        unsigned int iSignal;
        unsigned int iSampleMax;
        unsigned int iSampleMaxLeft;
        unsigned int iSampleMaxRight;
        unsigned int iSample;
        unsigned int delta;
        float maxValue;

        for (iSignal = 0; iSignal < xcorrs->nSignals; iSignal++) {

            delta = deltas->array[iSignal];
            iSampleMaxLeft = tdoas->array[0*xcorrs->nSignals + iSignal] + delta;
            iSampleMaxRight = tdoas->array[1*xcorrs->nSignals + iSignal] + delta;

            for (iSampleMax = iSampleMaxLeft; iSampleMax <= iSampleMaxRight; iSampleMax++) {

                maxValue = xcorrs->array[iSignal][iSampleMax];

                for (iSample = (iSampleMax-delta); iSample <= (iSampleMax+delta); iSample++) {

                    if (xcorrs->array[iSignal][iSample] > maxValue) {

                        maxValue = xcorrs->array[iSignal][iSample];

                    }

                }

                xcorrsMax->array[iSignal][iSampleMax] = maxValue;

            }

        }

    }

    void xcorr2xcorr_process_reset(xcorr2xcorr_obj * obj, const xcorrs_obj * xcorrs, const tdoas_obj * tdoas, const tdoas_obj * minmax, const deltas_obj * deltas, const unsigned int iPoint, xcorrs_obj * xcorrsReset) {

        unsigned int iSignal;
        unsigned int iSample;
        unsigned int nSamples;
        unsigned int delta;

        for (iSignal = 0; iSignal < xcorrs->nSignals; iSignal++) {

            iSample = minmax->array[0 * xcorrs->nSignals + iSignal];
            nSamples = (minmax->array[1 * xcorrs->nSignals + iSignal] - minmax->array[0 * xcorrs->nSignals + iSignal] + 1);

            memcpy(&(xcorrsReset->array[iSignal][iSample]), &(xcorrs->array[iSignal][iSample]), sizeof(float) * nSamples);

            delta = deltas->array[iSignal];
            iSample = tdoas->array[iPoint * tdoas->nPairs + iSignal] - delta;
            nSamples = 2 * delta + 1;

            memset(&(xcorrsReset->array[iSignal][iSample]), 0x00, sizeof(float) * nSamples);

        }

    }
