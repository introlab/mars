#ifndef __MARS_INIT_WINDOWING
#define __MARS_INIT_WINDOWING

    #include <math.h>

    #include "../signal/window.h"
    
    window_obj * windowing_hann(const unsigned int frameSize);

    window_obj * windowing_roothann(const unsigned int frameSize);

#endif

    