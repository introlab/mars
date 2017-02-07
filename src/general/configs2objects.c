
    #include "configs2objects.h"

    void configs2objects(objects * objs, const configs * cfgs, const arguments * args) {

        // Raw: input

        if (args->input_raw_file != NULL) {

            cfgs->src_raw_file->fileName = (char *) malloc(sizeof(char) * (strlen(args->input_raw_file)+1));
            strcpy(cfgs->src_raw_file->fileName, args->input_raw_file);

            objs->src_raw_file = src_raw_file_construct(cfgs->src_raw_file);

        }

        if (args->input_raw_soundcard != NULL) {

            printf("Not implemented yet.\n");
            exit(EXIT_FAILURE);

        }

        if (args->input_raw_socket != NULL) {

            printf("Not implemented yet.\n");
            exit(EXIT_FAILURE);

        }

        // Hops

        objs->msg_hops = msg_hops_construct(cfgs->msg_hops);

        // Raw: output

        if (args->output_raw_file != NULL) {

            printf("Not implemented yet.\n");
            exit(EXIT_FAILURE);

        }

        if (args->output_raw_soundcard != NULL) {

            printf("Not implemented yet.\n");
            exit(EXIT_FAILURE);
            
        }        

        if (args->output_raw_socket != NULL) {

            printf("Not implemented yet.\n");
            exit(EXIT_FAILURE);
            
        }  

        // SSL

        if ((args->output_pot_file_bin != NULL) ||
            (args->output_pot_file_xml != NULL) ||
            (args->output_track_file_bin != NULL) ||
            (args->output_track_file_xml != NULL) ||
            (args->verbose == 0x01) ||
            (args->force == 0x01)) {

            objs->mod_stft = mod_stft_construct(cfgs->mod_stft);
            objs->msg_spectra = msg_spectra_construct(cfgs->msg_spectra);
            objs->mod_ssl = mod_ssl_construct(cfgs->mod_ssl);
            objs->msg_pots = msg_pots_construct(cfgs->msg_pots);

            if (args->output_pot_file_bin != NULL) {

                cfgs->snk_pots->fileName = (char *) malloc(sizeof(char) * (strlen(args->output_pot_file_bin)+1));
                strcpy(cfgs->snk_pots->fileName, args->output_pot_file_bin);

                cfgs->snk_pots->format = 'b';

                objs->snk_pots = snk_pots_construct(cfgs->snk_pots);

            }

            if (args->output_pot_file_xml != NULL) {

                cfgs->snk_pots->fileName = (char *) malloc(sizeof(char) * (strlen(args->output_pot_file_xml)+1));
                strcpy(cfgs->snk_pots->fileName, args->output_pot_file_xml);

                cfgs->snk_pots->format = 'x';

                objs->snk_pots = snk_pots_construct(cfgs->snk_pots);

            }

        }

        // SST

        if ((args->output_track_file_bin != NULL) ||
            (args->output_track_file_xml != NULL) ||
            (args->verbose == 0x01) ||
            (args->force == 0x01)) {

            objs->mod_sst = mod_sst_construct(cfgs->mod_sst);
            objs->msg_tracks = msg_tracks_construct(cfgs->msg_tracks);

            if (args->output_track_file_bin != NULL) {

                cfgs->snk_tracks->fileName = (char *) malloc(sizeof(char) * (strlen(args->output_track_file_bin)+1));
                strcpy(cfgs->snk_tracks->fileName, args->output_track_file_bin);

                cfgs->snk_tracks->format = 'b';

                objs->snk_tracks = snk_tracks_construct(cfgs->snk_tracks);

            }           

            if (args->output_track_file_xml != NULL) {

                cfgs->snk_tracks->fileName = (char *) malloc(sizeof(char) * (strlen(args->output_track_file_xml)+1));
                strcpy(cfgs->snk_tracks->fileName, args->output_track_file_xml);

                cfgs->snk_tracks->format = 'x';

                objs->snk_tracks = snk_tracks_construct(cfgs->snk_tracks);

            }                   

        }

    }