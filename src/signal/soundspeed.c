    
    #include "soundspeed.h"

    soundspeed_obj * soundspeed_construct_zero(void) {

        soundspeed_obj * obj;

        obj = (soundspeed_obj *) malloc(sizeof(soundspeed_obj));

        obj->mu = 0.0f;
        obj->sigma = 0.0f;

        return obj;

    }

    void soundspeed_destroy(soundspeed_obj * obj) {

        free((void *) obj);

    }