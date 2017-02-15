#ifndef __MARS_SIGNAL_FIR
#define __MARS_SIGNAL_FIR

    #include <stdlib.h>
    #include <string.h>

    typedef struct firs_obj {

        unsigned int nSignals;
        unsigned int nCoefficients;
        float ** xs;

    } firs_obj;

    firs_obj * firs_construct_zero(unsigned int nSignals, unsigned int nCoefficients);

    void firs_destroy(firs_obj * obj);

#endif