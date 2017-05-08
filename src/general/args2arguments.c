
    #include "args2arguments.h"

    void args2arguments(arguments * args, int argc, char * argv[]) {

        int c;
        unsigned int nInputs;
        char configFile;

        nInputs = 0;
        configFile = 0x00;

        while ((c = getopt(argc,argv, "c:i:o:v")) != -1) {

            switch(c) {

                case 'c':

                    if (name_check_file_cfg(optarg) == 0) {

                        args->config_file = (char *) malloc(sizeof(char) * (strlen(optarg)+1));
                        strcpy(args->config_file, optarg);

                        configFile = 0x01;

                    }

                break;

                case 'i':

                    if (name_check_file_raw(optarg) == 0) {

                        args->input_raw_file = (char *) malloc(sizeof(char) * (strlen(optarg)+1));
                        strcpy(args->input_raw_file, optarg);

                        nInputs++;

                    }

                    if ((name_check_hw(optarg) == 0) || (name_check_plughw(optarg) == 0)) {

                        args->input_raw_soundcard = (char *) malloc(sizeof(char) * (strlen(optarg)+1));
                        strcpy(args->input_raw_soundcard, optarg);

                        nInputs++;

                    }          

                    if (name_check_file_wav(optarg) == 0) {

                        args->input_wav_file = (char *) malloc(sizeof(char) * (strlen(optarg)+1));
                        strcpy(args->input_wav_file, optarg);

                        nInputs++;

                    }                               

                break;

                case 'o':

                    if (name_check_file_raw(optarg) == 0) {

                        args->output_raw_file = (char *) malloc(sizeof(char) * (strlen(optarg)+1));
                        strcpy(args->output_raw_file, optarg);

                    }

                    if (name_check_hw(optarg) == 0) {

                        args->output_raw_soundcard = (char *) malloc(sizeof(char) * (strlen(optarg)+1));
                        strcpy(args->output_raw_soundcard, optarg);

                    }       

                    if (name_check_file_spectrabin(optarg) == 0) {

                        args->output_spectra_file_bin = (char *) malloc(sizeof(char) * (strlen(optarg)+1));
                        strcpy(args->output_spectra_file_bin, optarg);

                    }

                    if (name_check_file_xcsbin(optarg) == 0) {

                        args->output_xcs_file_bin = (char *) malloc(sizeof(char) * (strlen(optarg)+1));
                        strcpy(args->output_xcs_file_bin, optarg);

                    }

                    if (name_check_file_potbin(optarg) == 0) {

                        args->output_pot_file_bin = (char *) malloc(sizeof(char) * (strlen(optarg)+1));
                        strcpy(args->output_pot_file_bin, optarg);

                    }

                    if (name_check_file_potxml(optarg) == 0) {

                        args->output_pot_file_xml = (char *) malloc(sizeof(char) * (strlen(optarg)+1));
                        strcpy(args->output_pot_file_xml, optarg);

                    }                   

                    if (name_check_file_trackbin(optarg) == 0) {

                        args->output_track_file_bin = (char *) malloc(sizeof(char) * (strlen(optarg)+1));
                        strcpy(args->output_track_file_bin, optarg);

                    }

                    if (name_check_file_trackxml(optarg) == 0) {

                        args->output_track_file_xml = (char *) malloc(sizeof(char) * (strlen(optarg)+1));
                        strcpy(args->output_track_file_xml, optarg);

                    }                    

                    if (name_check_ipv4_trackxml(optarg) == 0) {

                        args->output_track_socket_xml = (char *) malloc(sizeof(char) * (strlen(optarg)+1));
                        strcpy(args->output_track_socket_xml, optarg);

                    }                       

                    if (name_check_ipv4_trackjson(optarg) == 0) {

                        args->output_track_socket_json = (char *) malloc(sizeof(char) * (strlen(optarg)+1));
                        strcpy(args->output_track_socket_json, optarg);

                    }   

                break;

                case 'v':

                    args->verbose = 0x01;

                break;

                default:

                    exit(EXIT_FAILURE);

                break;

            }

        }

        if (configFile == 0x00) {
            printf("Missing configuration file (.cfg)\n");
            exit(EXIT_FAILURE);
        }
        if (nInputs > 1) {
            printf("Too many inputs.\n");
            exit(EXIT_FAILURE);
        }
        if (nInputs == 0) {
            printf("No input specified.\n");
            exit(EXIT_FAILURE);
        }

    }