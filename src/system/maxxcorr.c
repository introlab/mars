    
    #include "maxxcorr.h"

    maxxcorr_obj * maxxcorr_construct(const unsigned int frameSize, const unsigned int delta, const signed int tdoaMin, const signed int tdoaMax) {

        maxxcorr_obj * obj;

        obj = (maxxcorr_obj *) malloc(sizeof(maxxcorr_obj));

        obj->frameSize = frameSize;
        obj->halfFrameSize = frameSize/2 + 1;
        obj->delta = delta;
        obj->tdoaMin = tdoaMin;
        obj->tdoaMax = tdoaMax;

        return obj;

    }

    void maxxcorr_destroy(maxxcorr_obj * obj) {

        free((void *) obj);

    }

    int maxxcorr_process(const maxxcorr_obj * obj, const vector_float * xcorrSrc, vector_float * xcorrDest) {

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