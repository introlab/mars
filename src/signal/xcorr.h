#ifndef __MARS_SIGNAL_XCORR
#define __MARS_SIGNAL_XCORR

    #include <stdlib.h>
    #include <string.h>
    #include <stdio.h>

    typedef struct xcorrs_obj {

        unsigned int nSignals;
        unsigned int frameSize;
        float * array;

    } xcorrs_obj;

    xcorrs_obj * xcorrs_construct_zero(const unsigned int nSignals, const unsigned int frameSize);

    void xcorrs_destroy(xcorrs_obj * obj);

    void xcorrs_printf(const xcorrs_obj * obj);

#endif