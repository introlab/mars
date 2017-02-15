#ifndef __MARS_INIT_LOWPASS
#define __MARS_INIT_LOWPASS

    #include <stdlib.h>
    #include <stdio.h>

    #include "../signal/impulse.h"

    impulse_obj * lowpass_init_factor(const unsigned int factor);

#endif