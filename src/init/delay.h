#ifndef __MARS_INIT_DELAY
#define __MARS_INIT_DELAY

    #include <math.h>

    #include "../signal/point.h"
    #include "../signal/mic.h"
    #include "../signal/tdoa.h"

    tdoas_obj * delay_tdoas(const points_obj * points, const mics_obj * mics, const float c, const unsigned int fS, const unsigned int frameSize, const unsigned int delta);

#endif

    