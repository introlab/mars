#ifndef __MARS_SINK_SPECTRA_FILE
#define __MARS_SINK_SPECTRA_FILE

    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include <math.h>
    #include <limits.h>

    #include "../message/msg_spectra.h"

    typedef struct snk_spectra_file_obj {

        char * fileName;
        FILE * fp;
        char format;

    } snk_spectra_file_obj;    

    typedef struct snk_spectra_file_cfg {

        char * fileName;
        char format;

    } snk_spectra_file_cfg;

    snk_spectra_file_obj * snk_spectra_file_construct(const snk_spectra_file_cfg * cfg);

    void snk_spectra_file_destroy(snk_spectra_file_obj * obj);

    void snk_spectra_file_process(snk_spectra_file_obj * obj, msg_spectra_obj * msg_spectra);

    void snk_spectra_file_process_bin(snk_spectra_file_obj * obj, msg_spectra_obj * msg_spectra);

    snk_spectra_file_cfg * snk_spectra_file_cfg_construct(void);

    void snk_spectra_file_cfg_destroy(snk_spectra_file_cfg * cfg);

#endif