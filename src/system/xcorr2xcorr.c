    
    #include "xcorr2xcorr.h"

    xcorr2xcorr_obj * xcorr2xcorr_construct(const unsigned int frameSize, const unsigned int delta, const signed int tdoaMin, const signed int tdoaMax) {

        xcorr2xcorr_obj * obj;

        obj = (xcorr2xcorr_obj *) malloc(sizeof(xcorr2xcorr_obj));

        obj->frameSize = frameSize;
        obj->halfFrameSize = frameSize/2 + 1;
        obj->delta = delta;
        obj->tdoaMin = tdoaMin;
        obj->tdoaMax = tdoaMax;

        return obj;

    }

    void xcorr2xcorr_destroy(xcorr2xcorr_obj * obj) {

        free((void *) obj);

    }

    int xcorr2xcorr_process(const xcorr2xcorr_obj * obj, const vector_float * xcorrSrc, vector_float * xcorrDest) {

        signed int tdoa;
        signed int delta;
        unsigned int index;
        float value;
        float maxValue;

        for (tdoa = obj->tdoaMin; tdoa <= obj->tdoaMax; tdoa++) {

            index = indexing_wrap(tdoa, obj->frameSize);
            maxValue = xcorrSrc->array[index];

            for (delta = 0; delta < obj->delta; delta++) {

                value = xcorrSrc->array[indexing_wrap(tdoa+(delta+1), obj->frameSize)];

                if (value > maxValue) {
                	maxValue = value;
                }

                value = xcorrSrc->array[indexing_wrap(tdoa-(delta+1), obj->frameSize)];

                if (value > maxValue) {
                	maxValue = value;
                }

            }

            xcorrDest->array[index] = maxValue;

        }

        return 0;

    }