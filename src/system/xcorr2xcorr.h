#ifndef __MARS_SYSTEM_XCORR
#define __MARS_SYSTEM_XCORR

    #include <stdlib.h>
    #include <string.h>

    #include "../signal/delta.h"
    #include "../signal/xcorr.h"
    #include "../signal/tdoa.h"

    typedef struct xcorr2xcorr_obj {

        unsigned int frameSize;     ///< Number of samples per frame.

    } xcorr2xcorr_obj;

    xcorr2xcorr_obj * xcorr2xcorr_construct_zero(const unsigned int frameSize);

    void xcorr2xcorr_destroy(xcorr2xcorr_obj * obj);

    void xcorr2xcorr_process_copy(xcorr2xcorr_obj * obj, const xcorrs_obj * xcorrsSrc, xcorrs_obj * xcorrsDest);

    void xcorr2xcorr_process_max(xcorr2xcorr_obj * obj, const xcorrs_obj * xcorrs, const tdoas_obj * tdoas, const deltas_obj * deltas, xcorrs_obj * xcorrsMax);

    void xcorr2xcorr_process_reset(xcorr2xcorr_obj * obj, const xcorrs_obj * xcorrs, const tdoas_obj * tdoas, const tdoas_obj * minmax, const deltas_obj * deltas, const unsigned int iPoint, xcorrs_obj * xcorrsReset);

#endif