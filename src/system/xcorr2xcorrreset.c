    
    #include "xcorr2xcorrreset.h"

    xcorr2xcorrreset_obj * xcorr2xcorrreset_construct(const unsigned int frameSize, const unsigned int winSize) {

        xcorr2xcorrreset_obj * obj;

        obj = (xcorr2xcorrreset_obj *) malloc(sizeof(xcorr2xcorrreset_obj));

        obj->frameSize = frameSize;
        obj->winSize = winSize;
        obj->halfWinSize = (winSize-1) / 2;

        return obj;

    }

    void xcorr2xcorrreset_destroy(xcorr2xcorrreset_obj * obj) {

        free((void *) obj);

    }

    int xcorr2xcorrreset_process(const xcorr2xcorrreset_obj * obj, const vector_float * xcorrs, const signed int tdoa, vector_float * xcorrsReset) {

        unsigned int index;
        signed int delta;

        vector_float_copy(xcorrs, xcorrsReset);

        for (delta = -1 * ((signed int) obj->halfWinSize); delta <= ((signed int) obj->halfWinSize); delta++) {

            index = indexing_wrap((tdoa + delta), obj->frameSize);
            xcorrsReset->array[index] = 0.0f;

        }

        return 0;

    }
