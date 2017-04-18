#ifndef __MARS_SIGNAL_DELTA
#define __MARS_SIGNAL_DELTA

    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>

    typedef struct deltas_obj {

        unsigned int nPairs;
        unsigned int * array;

    } deltas_obj;

    deltas_obj * deltas_construct_zero(const unsigned int nPairs);

    void deltas_destroy(deltas_obj * obj);

    void deltas_printf(const deltas_obj * obj);

#endif