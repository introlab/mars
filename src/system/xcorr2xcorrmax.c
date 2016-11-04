    
    #include "xcorr2xcorrmax.h"

    xcorr2xcorrmax_obj * xcorr2xcorrmax_construct(const unsigned int frameSize, const unsigned int nMics, const unsigned int winSize, const signed int lowValue, const signed int highValue) {

        xcorr2xcorrmax_obj * obj;

        obj = (xcorr2xcorrmax_obj *) malloc(sizeof(xcorr2xcorrmax_obj));

        obj->frameSize = frameSize;
        obj->nMics = nMics;
        obj->nPairs = (nMics-1) * nMics / 2;
        obj->winSize = winSize;
        obj->halfWinSize = (winSize - 1) / 2;
        obj->lowValue = lowValue;
        obj->highValue = highValue;

        return obj;

    }

    void xcorr2xcorrmax_destroy(xcorr2xcorrmax_obj * obj) {

        free((void *) obj);

    }

    int xcorr2xcorrmax_process(const xcorr2xcorrmax_obj * obj, const vector_float * xcorrs, vector_float * xcorrsMax) {

        unsigned int iPair;
        signed int index;
        unsigned int indexWrap;
        signed int delta;
        signed int indexdelta;
        unsigned int indexdeltaWrap;
        float sample;
        float max;

        for (index = obj->lowValue; index <= obj->highValue; index++) {

            max = -INFINITY;

            for (delta = -1 * ((signed int) obj->halfWinSize); delta <= ((signed int) obj->halfWinSize); delta++) {

                indexdelta = index + delta;
                indexdeltaWrap = indexing_wrap(indexdelta, obj->frameSize);
                sample = xcorrs->array[indexdeltaWrap];

                if (sample > max) {
                    max = sample;
                }

            }

            indexWrap = indexing_wrap(index, obj->frameSize);
            xcorrsMax->array[indexWrap] = max;

        }

        return 0;

    }