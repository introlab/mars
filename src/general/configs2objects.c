
    #include "configs2objects.h"

    void configs2objects(objects * objs, const configs * cfgs, const arguments * args) {

        // Raw: input

        if (args->input_raw_file != NULL) {

            cfgs->src_raw_file->fileName = (char *) malloc(sizeof(char) * (strlen(args->input_raw_file)+1));
            strcpy(cfgs->src_raw_file->fileName, args->input_raw_file);

            objs->src_raw_file = src_raw_file_construct(cfgs->src_raw_file);

        }

        if (args->input_raw_soundcard != NULL) {

            cfgs->src_raw_soundcard->cardName = (char *) malloc(sizeof(char) * (strlen(args->input_raw_soundcard) + 1));
            strcpy(cfgs->src_raw_soundcard->cardName, args->input_raw_soundcard);

            objs->src_raw_soundcard = src_raw_soundcard_construct(cfgs->src_raw_soundcard);

        }

        if (args->input_raw_socket != NULL) {

            printf("Not implemented yet.\n");
            exit(EXIT_FAILURE);

        }

        // Hops

        objs->msg_hops_raw_in = msg_hops_construct(cfgs->msg_hops_raw_in); 
        objs->mod_resample_raw_in = mod_resample_construct(cfgs->mod_resample_raw_in);
        objs->msg_hops_raw = msg_hops_construct(cfgs->msg_hops_raw);

        // Raw: output

        if (args->output_raw_file != NULL) {

            cfgs->snk_raw_file->fileName = (char *) malloc(sizeof(char) * (strlen(args->output_raw_file)+1));
            strcpy(cfgs->snk_raw_file->fileName, args->output_raw_file);

            objs->snk_raw_file = snk_raw_file_construct(cfgs->snk_raw_file);

            objs->mod_resample_raw_out = mod_resample_construct(cfgs->mod_resample_raw_out);
            objs->msg_hops_raw_out = msg_hops_construct(cfgs->msg_hops_raw_out);

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

                cfgs->snk_pots_file->fileName = (char *) malloc(sizeof(char) * (strlen(args->output_pot_file_bin)+1));
                strcpy(cfgs->snk_pots_file->fileName, args->output_pot_file_bin);

                cfgs->snk_pots_file->format = 'b';

                objs->snk_pots_file = snk_pots_file_construct(cfgs->snk_pots_file);

            }

            if (args->output_pot_file_xml != NULL) {

                cfgs->snk_pots_file->fileName = (char *) malloc(sizeof(char) * (strlen(args->output_pot_file_xml)+1));
                strcpy(cfgs->snk_pots_file->fileName, args->output_pot_file_xml);

                cfgs->snk_pots_file->format = 'x';

                objs->snk_pots_file = snk_pots_file_construct(cfgs->snk_pots_file);

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

                cfgs->snk_tracks_file->fileName = (char *) malloc(sizeof(char) * (strlen(args->output_track_file_bin)+1));
                strcpy(cfgs->snk_tracks_file->fileName, args->output_track_file_bin);

                cfgs->snk_tracks_file->format = 'b';

                objs->snk_tracks_file = snk_tracks_file_construct(cfgs->snk_tracks_file);

            }           

            if (args->output_track_file_xml != NULL) {

                cfgs->snk_tracks_file->fileName = (char *) malloc(sizeof(char) * (strlen(args->output_track_file_xml)+1));
                strcpy(cfgs->snk_tracks_file->fileName, args->output_track_file_xml);

                cfgs->snk_tracks_file->format = 'x';

                objs->snk_tracks_file = snk_tracks_file_construct(cfgs->snk_tracks_file);

            }                   

        }

    }