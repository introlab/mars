    
    #include "msg_pots.h"

    msg_pots_obj * msg_pots_construct(void) {

        msg_pots_obj * obj;

        obj = (msg_pots_obj *) malloc(sizeof(msg_pots_obj));

        obj->id = 0;
        obj->samples = (float *) malloc(sizeof(float) * 4);

        return obj;

    }

    void msg_pots_destroy(msg_pots_obj * obj) {

        free((void *) obj->samples);

        free((void *) obj);

    }