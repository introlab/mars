#ifndef __MARS_SIGNAL_FREQ
#define __MARS_SIGNAL_FREQ

    #include <stdlib.h>
    #include <string.h>
    #include <stdio.h>

    typedef struct freqs_obj {

        unsigned int nSignals;
        unsigned int halfFrameSize;
        float ** array;

    } freqs_obj;

    freqs_obj * freqs_construct_zero(const unsigned int nSignals, const unsigned int halfFrameSize);

    void freqs_destroy(freqs_obj * obj);

    void freqs_printf(const freqs_obj * obj);

#endif