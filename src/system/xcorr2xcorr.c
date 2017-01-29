    
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

    void xcorr2xcorr_process_max_single(xcorr2xcorr_obj * obj, const xcorr_obj * xcorr, const unsigned int minTdoa, const unsigned maxTdoa, const unsigned int delta, xcorr_obj * xcorrMax) {

        unsigned int iSampleMax;
        unsigned int iSample;
        float maxValue;

        for (iSampleMax = minTdoa; iSampleMax <= maxTdoa; iSampleMax++) {

            maxValue = xcorr->array[iSampleMax];

            for (iSample = (iSampleMax-delta); iSample <= (iSampleMax+delta); iSample++) {

                if (xcorr->array[iSample] > maxValue) {
                	maxValue = xcorr->array[iSample];
                }

            }

            xcorrMax->array[iSampleMax] = maxValue;

        }

    }

    void xcorr2xcorr_process_reset_single(xcorr2xcorr_obj * obj, const xcorr_obj * xcorr, const unsigned int tdoa, const unsigned int minTdoa, const unsigned maxTdoa, const unsigned int delta, xcorr_obj * xcorrReset) {

        unsigned int iSample;

        for (iSample = minTdoa; iSample <= maxTdoa; iSample++) {

            xcorrReset->array[iSample] = xcorr->array[iSample];

        }

        for (iSample = (tdoa-delta); iSample <= (tdoa+delta); iSample++) {

            xcorrReset->array[iSample] = 0.0f;

        }

    }

    void xcorr2xcorr_process_max_many(xcorr2xcorr_obj * obj, const xcorrs_obj * xcorrs, const tdoa_obj * minTdoas, const tdoa_obj * maxTdoas, const unsigned int delta, xcorrs_obj * xcorrsMax) {

        unsigned int iSignal;

        for (iSignal = 0; iSignal < xcorrs->nSignals; iSignal++) {

            xcorr2xcorr_process_max_single(obj, xcorrs->array[iSignal], minTdoas->array[iSignal], maxTdoas->array[iSignal], delta, xcorrsMax->array[iSignal]);

        }

    }

    void xcorr2xcorr_process_reset_many(xcorr2xcorr_obj * obj, const xcorrs_obj * xcorrs, const tdoa_obj * tdoa, const tdoa_obj * minTdoas, const tdoa_obj * maxTdoas, const unsigned int delta, xcorrs_obj * xcorrsReset) {

        unsigned int iSignal;

        for (iSignal = 0; iSignal < xcorrs->nSignals; iSignal++) {

            xcorr2xcorr_process_reset_single(obj, xcorrs->array[iSignal], tdoa->array[iSignal], minTdoas->array[iSignal], maxTdoas->array[iSignal], delta, xcorrsReset->array[iSignal]);

        }

    }
