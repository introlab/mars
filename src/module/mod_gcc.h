#ifndef __MARS_MODULE_GCC
#define __MARS_MODULE_GCC

    #include "../signal/freq.h"
    #include "../signal/mic.h"
    #include "../signal/xcorr.h"
    #include "../system/freq2freq.h"
    #include "../system/freq2xcorr.h"
    #include "../message/msg_spectra.h"
    #include "../message/msg_xcs.h"
 
    #include <stdlib.h>

    typedef struct mod_gcc_obj {

        unsigned int nMics;
        unsigned int nPairs;
        unsigned int frameSize;

        freqs_obj * phasors;
        freqs_obj * products;
        freqs_obj * smooths;
        freq2freq_obj * freq2freq;
        freq2xcorr_obj * freq2xcorr;

    } mod_gcc_obj;

    typedef struct mod_gcc_cfg {
        
        unsigned int nMics;
        unsigned int frameSize;
        float epsilon;
        float alpha;

    } mod_gcc_cfg;

    mod_gcc_obj * mod_gcc_construct(const mod_gcc_cfg * cfg);

    void mod_gcc_destroy(mod_gcc_obj * obj);

    void mod_gcc_process(mod_gcc_obj * obj, const msg_spectra_obj * msg_spectra, msg_xcs_obj * msg_xcs);

    mod_gcc_cfg * mod_gcc_cfg_construct(void);

    void mod_gcc_cfg_destroy(mod_gcc_cfg * cfg);

#endif