#ifndef __MARS_SINK_XCS_FILE
#define __MARS_SINK_XCS_FILE

    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include <math.h>
    #include <limits.h>

    #include "../message/msg_xcs.h"

    typedef struct snk_xcs_file_obj {

        char * fileName;
        FILE * fp;
        char format;

    } snk_xcs_file_obj;    

    typedef struct snk_xcs_file_cfg {

        char * fileName;
        char format;

    } snk_xcs_file_cfg;

    snk_xcs_file_obj * snk_xcs_file_construct(const snk_xcs_file_cfg * cfg);

    void snk_xcs_file_destroy(snk_xcs_file_obj * obj);

    void snk_xcs_file_process(snk_xcs_file_obj * obj, msg_xcs_obj * msg_xcs);

    void snk_xcs_file_process_bin(snk_xcs_file_obj * obj, msg_xcs_obj * msg_xcs);

    snk_xcs_file_cfg * snk_xcs_file_cfg_construct(void);

    void snk_xcs_file_cfg_destroy(snk_xcs_file_cfg * cfg);

#endif