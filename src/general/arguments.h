#ifndef __MARS_GENERAL_ARGUMENTS
#define __MARS_GENERAL_ARGUMENTS

    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include <getopt.h>

    typedef struct arguments {

        char * config_file;

        char * input_raw_file;
        char * input_raw_soundcard;
        char * input_raw_socket;
        char * output_raw_file;
        char * output_raw_soundcard;
        char * output_raw_socket;

        char * output_pot_file_bin;
        char * output_pot_file_xml;        
        char * output_track_file_bin;
        char * output_track_file_xml;

        char verbose;
        char force;

    } arguments;

    arguments * arguments_construct_null(void);

    void arguments_destroy(arguments * args);

    void arguments_printf(const arguments * args);

#endif