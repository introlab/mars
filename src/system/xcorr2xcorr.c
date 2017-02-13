    
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

    void xcorr2xcorr_process_max(xcorr2xcorr_obj * obj, const xcorrs_obj * xcorrs, const tdoas_obj * tdoas, const unsigned int delta, xcorrs_obj * xcorrsMax) {

        unsigned int iSignal;
        unsigned int iSampleMax;
        unsigned int iSample;
        float maxValue;

        for (iSignal = 0; iSignal < xcorrs->nSignals; iSignal++) {

            for (iSampleMax = tdoas->arrayMin[iSignal]; iSampleMax <= tdoas->arrayMax[iSignal]; iSampleMax++) {

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

    void xcorr2xcorr_process_reset(xcorr2xcorr_obj * obj, const xcorrs_obj * xcorrs, const tdoas_obj * tdoas, const unsigned int delta, const unsigned int iPoint, xcorrs_obj * xcorrsReset) {

        unsigned int iSignal;
        unsigned short iSample;
        unsigned short nSamples;

        for (iSignal = 0; iSignal < xcorrs->nSignals; iSignal++) {

            iSample = tdoas->arrayMin[iSignal];
            nSamples = (tdoas->arrayMax[iSignal] - tdoas->arrayMin[iSignal] + 1);

            memcpy(&(xcorrsReset->array[iSignal][iSample]), &(xcorrs->array[iSignal][iSample]), sizeof(float) * nSamples);

            iSample = tdoas->array[iPoint][iSignal] - delta;
            nSamples = 2 * delta + 1;

            memset(&(xcorrsReset->array[iSignal][iSample]), 0x00, sizeof(float) * nSamples);

        }

    }
