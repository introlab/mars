#ifndef __MARS_SYSTEM_XCORR2AIMG
#define __MARS_SYSTEM_XCORR2AIMG

    #include <stdlib.h>

    #include "../signal/tdoa.h"
    #include "../signal/index.h"
    #include "../signal/xcorr.h"
    #include "../signal/aimg.h"

    //! Update the states of the particle filter
    typedef struct xcorr2aimg_obj {

        unsigned int aimgSize;      ///< Number of points scanned.

    } xcorr2aimg_obj;

    xcorr2aimg_obj * xcorr2aimg_construct_zero(const unsigned int aimgSize);

    void xcorr2aimg_destroy(xcorr2aimg_obj * obj);

    void xcorr2aimg_process(xcorr2aimg_obj * obj, const tdoas_obj * tdoas, const indexes_obj * indexes, const unsigned int iCoarse, const xcorrs_obj * xcorrs, aimg_obj * aimg);

#endif