#ifndef __MARS_MODULE_SSL
#define __MARS_MODULE_SSL

    #include <stdlib.h>
    #include <string.h>

    #include "../signal/aimg.h"
    #include "../signal/mic.h"
    #include "../signal/freq.h"
    #include "../signal/soundspeed.h"
    #include "../signal/xcorr.h"
    
    #include "../system/freq2freq.h"
    #include "../system/freq2xcorr.h"
    #include "../system/xcorr2aimg.h"
    #include "../system/xcorr2xcorr.h"

    #include "../init/scanning.h"

    #include "../message/msg_spectra.h"
    #include "../message/msg_pots.h"


    typedef struct mod_ssl_obj {

        unsigned int nMics;
        unsigned int nPairs;
        unsigned int nPots;
        unsigned int nScans;

        scans_obj * scans;

        unsigned int r;
        unsigned int R;

        freqs_obj * phasors;
        freqs_obj * products;
        freqs_obj * smooths;
        xcorrs_obj ** xcorrsReset;
        xcorrs_obj *** xcorrsMax;
        aimg_obj *** aimgs;

        freq2freq_obj * freq2freq;
        freq2xcorr_obj * freq2xcorr;
        xcorr2xcorr_obj * xcorr2xcorr;
        xcorr2aimg_obj ** xcorr2aimg;

        pots_obj * pots;

    } mod_ssl_obj;

    typedef struct mod_ssl_cfg {

        mics_obj * mics;
        unsigned int nPots;
        unsigned int fS;
        soundspeed_obj * soundspeed;
        unsigned int frameSize;
        float epsilon;
        float alpha;
        unsigned int R;
        char * shape;
        
        unsigned int nLevels;
        unsigned int * levels;
        signed int * deltas;
        unsigned int nMatches;
        float probMin;
        unsigned int nRefinedLevels;

    } mod_ssl_cfg;

    mod_ssl_obj * mod_ssl_construct(const mod_ssl_cfg * cfg);

    void mod_ssl_destroy(mod_ssl_obj * obj);

    void mod_ssl_process(mod_ssl_obj * obj, msg_spectra_obj * msg_spectra, msg_pots_obj * msg_pots);

    mod_ssl_cfg * mod_ssl_cfg_construct(void);

    void mod_ssl_cfg_destroy(mod_ssl_cfg * cfg);

#endif