#ifndef __MARS_SIGNAL_POT
#define __MARS_SIGNAL_POT

    #include <stdlib.h>
    #include <string.h>
    #include <stdio.h>

    typedef struct pots_obj {

        unsigned int nPots;
        float * array;

    } pots_obj;

    pots_obj * pots_construct_zero(const unsigned int nPots);

    void pots_destroy(pots_obj * obj);

    void pots_printf(const pots_obj * obj);

#endif