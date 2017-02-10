#ifndef __MARS_SINK_POTS_FILE
#define __MARS_SINK_POTS_FILE

    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include <math.h>
    #include <limits.h>

    #include "../message/msg_pots.h"

    typedef struct snk_pots_file_obj {

        char * fileName;
        FILE * fp;
        char format;

    } snk_pots_file_obj;    

    typedef struct snk_pots_file_cfg {

        char * fileName;
        char format;

    } snk_pots_file_cfg;

    snk_pots_file_obj * snk_pots_file_construct(const snk_pots_file_cfg * cfg);

    void snk_pots_file_destroy(snk_pots_file_obj * obj);

    void snk_pots_file_process(snk_pots_file_obj * obj, msg_pots_obj * msg_pots);

    void snk_pots_file_process_xml(snk_pots_file_obj * obj, msg_pots_obj * msg_pots);

    void snk_pots_file_process_bin(snk_pots_file_obj * obj, msg_pots_obj * msg_pots);

    snk_pots_file_cfg * snk_pots_file_cfg_construct(void);

    void snk_pots_file_cfg_destroy(snk_pots_file_cfg * cfg);

#endif