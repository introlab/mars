#ifndef __MARS_SYSTEM_HOP2FRAME
#define __MARS_SYSTEM_HOP2FRAME

    #include <stdlib.h>
    #include <string.h>

    #include "../signal/hop.h"
    #include "../signal/frame.h"

    typedef struct hop2frame_obj {

        unsigned int hopSize;
        unsigned int frameSize;

    } hop2frame_obj;

    hop2frame_obj * hop2frame_construct_zero(const unsigned int hopSize, const unsigned int frameSize);

    void hop2frame_destroy(hop2frame_obj * obj);

    void hop2frame_process(hop2frame_obj * obj, const hops_obj * hops, frames_obj * frames);

#endif