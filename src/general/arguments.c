
    #include "arguments.h"

    arguments * arguments_construct_null(void) {

        arguments * args;

        args = (arguments *) malloc(sizeof(arguments));

        args->config_file = (char *) NULL;
        args->input_raw_file = (char *) NULL;
        args->input_raw_soundcard = (char *) NULL;
        args->input_wav_file = (char *) NULL;
        args->output_raw_file = (char *) NULL;
        args->output_raw_soundcard = (char *) NULL;
        args->output_raw_socket = (char *) NULL;
        args->output_spectra_file_bin = (char *) NULL;
        args->output_xcs_file_bin = (char *) NULL;
        args->output_pot_file_bin = (char *) NULL;
        args->output_pot_file_xml = (char *) NULL;
        args->output_track_file_bin = (char *) NULL;
        args->output_track_file_xml = (char *) NULL;
        args->output_track_socket_xml = (char *) NULL;
        args->output_track_socket_json = (char *) NULL;
        args->verbose = 0x00;

        return args;

    }

    void arguments_destroy(arguments * args) {

        if (args->config_file != NULL) {
            free((void *) args->config_file);    
        }

        if (args->input_raw_file != NULL) {
            free((void *) args->input_raw_file);
        }
         
        if (args->input_raw_soundcard != NULL) {
            free((void *) args->input_raw_soundcard);
        }
         
        if (args->input_wav_file != NULL) {
            free((void *) args->input_wav_file);
        }

        if (args->output_raw_file != NULL) {
            free((void *) args->output_raw_file);
        }

        if (args->output_raw_soundcard != NULL) {
            free((void *) args->output_raw_soundcard);
        }

        if (args->output_raw_socket != NULL) {
            free((void *) args->output_raw_socket);
        } 

        if (args->output_spectra_file_bin != NULL) {
            free((void *) args->output_spectra_file_bin);
        }

        if (args->output_xcs_file_bin != NULL) {
            free((void *) args->output_xcs_file_bin);
        }

        if (args->output_pot_file_bin != NULL) {
            free((void *) args->output_pot_file_bin);
        }

        if (args->output_pot_file_xml != NULL) {
            free((void *) args->output_pot_file_xml);
        }

        if (args->output_track_file_bin != NULL) {
            free((void *) args->output_track_file_bin);
        }

        if (args->output_track_file_xml != NULL) {
            free((void *) args->output_track_file_xml);
        }        

        if (args->output_track_socket_xml != NULL) {
            free((void *) args->output_track_socket_xml);
        }        

        if (args->output_track_socket_json != NULL) {
            free((void *) args->output_track_socket_json);
        }  

        free((void *) args);

    }

    void arguments_printf(const arguments * args) {

        printf("config_file: %s\n",args->config_file);
        printf("input_raw_file: %s\n",args->input_raw_file);
        printf("input_raw_soundcard: %s\n",args->input_raw_soundcard);
        printf("input_wav_file: %s\n",args->input_wav_file);
        printf("output_raw_file: %s\n",args->output_raw_file);
        printf("output_raw_soundcard: %s\n",args->output_raw_soundcard);
        printf("output_raw_socket: %s\n",args->output_raw_socket);
        printf("output_pot_file_bin: %s\n",args->output_pot_file_bin);
        printf("output_pot_file_xml: %s\n",args->output_pot_file_xml);
        printf("output_track_file_bin: %s\n",args->output_track_file_bin);
        printf("output_track_file_xml: %s\n",args->output_track_file_xml);
        printf("output_track_socket_xml: %s\n",args->output_track_socket_xml);
        printf("output_track_socket_json: %s\n",args->output_track_socket_json);

    }
