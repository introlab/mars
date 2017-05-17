#ifndef __MARS_MODULE_STFT
#define __MARS_MODULE_STFT

    #include "../system/hop2frame.h"
    #include "../signal/frame.h"
    #include "../system/frame2freq.h"
    #include "../message/msg_hops.h"
    #include "../message/msg_spectra.h"

 
    typedef struct mod_stft_obj {

        hop2frame_obj * hop2frame;
        frames_obj * frames;
        frame2freq_obj * frame2freq;

    } mod_stft_obj;

    typedef struct mod_stft_cfg {
        
        unsigned int nChannels;
        unsigned int hopSize;
        unsigned int frameSize;

    } mod_stft_cfg;

    mod_stft_obj * mod_stft_construct(const mod_stft_cfg * cfg);

    void mod_stft_destroy(mod_stft_obj * obj);

    void mod_stft_process(mod_stft_obj * obj, const msg_hops_obj * msg_hops, msg_spectra_obj * msg_spectra);

    mod_stft_cfg * mod_stft_cfg_construct(void);

    void mod_stft_cfg_destroy(mod_stft_cfg * cfg);

#endif