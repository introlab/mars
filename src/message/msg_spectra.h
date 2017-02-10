#ifndef __MARS_MESSAGE_SPECTRA
#define __MARS_MESSAGE_SPECTRA

    #include <stdlib.h>

    #include "../signal/freq.h"

    typedef struct msg_spectra_obj {

        unsigned long long timeStamp;
        freqs_obj * freqs;

    } msg_spectra_obj;

    typedef struct msg_spectra_cfg {

        unsigned int frameSize;
        unsigned int nMics;

    } msg_spectra_cfg;

    msg_spectra_obj * msg_spectra_construct(const msg_spectra_cfg * cfg);

    void msg_spectra_destroy(msg_spectra_obj * obj);

    msg_spectra_cfg * msg_spectra_cfg_construct(void);

    void msg_spectra_cfg_destroy(msg_spectra_cfg * cfg);

#endif