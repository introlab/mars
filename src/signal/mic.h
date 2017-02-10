#ifndef __MARS_SIGNAL_MIC
#define __MARS_SIGNAL_MIC

    #include <stdlib.h>
    #include <string.h>

    typedef struct mics_obj {

        unsigned int nMics;
        float * array;

    } mics_obj;

    mics_obj * mics_construct_zero(const unsigned int nMics);

    void mics_destroy(mics_obj * obj);

#endif