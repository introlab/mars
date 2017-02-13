#ifndef __MARS_SIGNAL_FRAME
#define __MARS_SIGNAL_FRAME

    #include <stdlib.h>
    #include <string.h>
    #include <stdio.h>

    typedef struct frames_obj {

        unsigned int nSignals;
        unsigned int frameSize;
        float ** array;

    } frames_obj;

    frames_obj * frames_construct_zero(const unsigned int nSignals, const unsigned int frameSize);

    void frames_destroy(frames_obj * obj);

    void frames_printf(const frames_obj * obj);

#endif