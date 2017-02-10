#ifndef __MARS_SYSTEM_FREQ2FREQ
#define __MARS_SYSTEM_FREQ2FREQ

    #include <stdlib.h>
    #include <math.h>

    #include "../signal/freq.h"

    typedef struct freq2freq_obj {

        unsigned int halfFrameSize;
        float epsilon;
        float alpha;

    } freq2freq_obj;

    freq2freq_obj * freq2freq_construct_zero(const unsigned int halfFrameSize, const float epsilon, const float alpha);

    void freq2freq_destroy(freq2freq_obj * obj);

    void freq2freq_process_phasor(freq2freq_obj * obj, const freqs_obj * freqs, freqs_obj * phasors);

    void freq2freq_process_product(freq2freq_obj * obj, const freqs_obj * phasors1, const freqs_obj * phasors2, freqs_obj * phasors12);

    void freq2freq_process_smooth(freq2freq_obj * obj, const freqs_obj * phasors, freqs_obj * smooths);

#endif