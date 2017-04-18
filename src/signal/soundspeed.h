#ifndef __MARS_SIGNAL_SOUNDSPEED
#define __MARS_SIGNAL_SOUNDSPEED

    #include <stdlib.h>

    typedef struct soundspeed_obj {

        float mu;
        float sigma;

    } soundspeed_obj;

    soundspeed_obj * soundspeed_construct_zero(void);

    void soundspeed_destroy(soundspeed_obj * obj);

#endif