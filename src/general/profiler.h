#ifndef __MARS_GENERAL_PROFILER
#define __MARS_GENERAL_PROFILER

    #include <stdlib.h>

    typedef struct profiler_obj {
    
        float resampling;
        float stft;
        float ssl;
        float sst;

        float duration;
        float fS;

    } profiler_obj;

    profiler_obj * profiler_construct_zero(const unsigned int fS);

    void profiler_destroy(profiler_obj * obj);

#endif