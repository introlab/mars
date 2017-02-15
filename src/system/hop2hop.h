#ifndef __MARS_SYSTEM_HOP2HOP
#define __MARS_SYSTEM_HOP2HOP

    #include <stdlib.h>
    #include <string.h>

    #include "../signal/fir.h"
    #include "../signal/hop.h"
    #include "../signal/impulse.h"

    typedef struct hop2hop_obj {

        unsigned int nHops;

    } hop2hop_obj;

    hop2hop_obj * hop2hop_construct_zero(const unsigned int nHops);

    void hop2hop_destroy(hop2hop_obj * obj);

    void hop2hop_filter(const hop2hop_obj * obj, const hops_obj * hopsIn, impulse_obj * impulse, firs_obj * firs, hops_obj * hopsOut);

    void hop2hop_downsample(const hop2hop_obj * obj, const hops_obj * hopsIn, hops_obj * hopsOut);

    void hop2hop_upsample(const hop2hop_obj * obj, const hops_obj * hopsIn, hops_obj * hopsOut);

#endif