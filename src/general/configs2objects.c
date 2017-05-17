
    #include "configs2objects.h"

    void configs2objects(objects * objs, const configs * cfgs, const arguments * args) {

        // Raw: input

        if (args->input_raw_file != NULL) {

            strcpy(cfgs->src_raw_file->fileName, args->input_raw_file);

            objs->src_raw_file = src_raw_file_construct(cfgs->src_raw_file);

        }

        if (args->input_raw_soundcard != NULL) {

            strcpy(cfgs->src_raw_soundcard->cardName, args->input_raw_soundcard);

            objs->src_raw_soundcard = src_raw_soundcard_construct(cfgs->src_raw_soundcard);

        }

        if (args->input_wav_file != NULL) {

            strcpy(cfgs->src_wav_file->fileName, args->input_wav_file);

            objs->src_wav_file = src_wav_file_construct(cfgs->src_wav_file);

        }

        // Hops

        objs->msg_hops_raw_in = msg_hops_construct(cfgs->msg_hops_raw_in); 
        objs->mod_resample_raw_in = mod_resample_construct(cfgs->mod_resample_raw_in);
        objs->msg_hops_raw = msg_hops_construct(cfgs->msg_hops_raw);

        // Raw: output

        if (args->output_raw_file != NULL) {

            strcpy(cfgs->snk_raw_file->fileName, args->output_raw_file);

            objs->snk_raw_file = snk_raw_file_construct(cfgs->snk_raw_file);
            objs->mod_resample_raw_out = mod_resample_construct(cfgs->mod_resample_raw_out);
            objs->msg_hops_raw_out = msg_hops_construct(cfgs->msg_hops_raw_out);

        }

        if (args->output_raw_socket != NULL) {

            parser_extract_ipv4_ip(args->output_raw_socket, cfgs->snk_raw_socket->ipAddress);
            parser_extract_ipv4_port(args->output_raw_socket, cfgs->snk_raw_socket->portNumber);
            cfgs->snk_raw_socket->format = 'b';

            objs->snk_raw_socket = snk_raw_socket_construct(cfgs->snk_raw_socket);
            objs->mod_resample_raw_out = mod_resample_construct(cfgs->mod_resample_raw_out);
            objs->msg_hops_raw_out = msg_hops_construct(cfgs->msg_hops_raw_out);           

        }

        if (args->output_raw_soundcard != NULL) {

            printf("Not implemented yet.\n");
            exit(EXIT_FAILURE);
            
        }        

        // STFT

        objs->mod_stft = mod_stft_construct(cfgs->mod_stft);
        objs->msg_spectra = msg_spectra_construct(cfgs->msg_spectra);

        if (args->output_spectra_file_bin != NULL) {

            strcpy(cfgs->snk_spectra_file->fileName, args->output_spectra_file_bin);
            cfgs->snk_spectra_file->format = 'b';

            objs->snk_spectra_file = snk_spectra_file_construct(cfgs->snk_spectra_file);

        }

        // GCC

        objs->mod_gcc = mod_gcc_construct(cfgs->mod_gcc);
        objs->msg_xcs = msg_xcs_construct(cfgs->msg_xcs);

        if (args->output_xcs_file_bin != NULL) {

            strcpy(cfgs->snk_xcs_file->fileName, args->output_xcs_file_bin);
            cfgs->snk_xcs_file->format = 'b';

            objs->snk_xcs_file = snk_xcs_file_construct(cfgs->snk_xcs_file);

        }

        // SSL

        objs->mod_ssl = mod_ssl_construct(cfgs->mod_ssl);
        objs->msg_pots = msg_pots_construct(cfgs->msg_pots);

        if (args->output_pot_file_bin != NULL) {

            strcpy(cfgs->snk_pots_file->fileName, args->output_pot_file_bin);
            cfgs->snk_pots_file->format = 'b';

            objs->snk_pots_file = snk_pots_file_construct(cfgs->snk_pots_file);

        }

        if (args->output_pot_file_xml != NULL) {

            strcpy(cfgs->snk_pots_file->fileName, args->output_pot_file_xml);
            cfgs->snk_pots_file->format = 'x';

            objs->snk_pots_file = snk_pots_file_construct(cfgs->snk_pots_file);

        }

        // SST

        objs->mod_sst = mod_sst_construct(cfgs->mod_sst);
        objs->msg_tracks = msg_tracks_construct(cfgs->msg_tracks);

        if (args->output_track_file_bin != NULL) {

            strcpy(cfgs->snk_tracks_file->fileName, args->output_track_file_bin);
            cfgs->snk_tracks_file->format = 'b';

            objs->snk_tracks_file = snk_tracks_file_construct(cfgs->snk_tracks_file);

        }           

        if (args->output_track_file_xml != NULL) {

            strcpy(cfgs->snk_tracks_file->fileName, args->output_track_file_xml);
            cfgs->snk_tracks_file->format = 'x';

            objs->snk_tracks_file = snk_tracks_file_construct(cfgs->snk_tracks_file);

        }                  

        if (args->output_track_socket_xml != NULL) {

            parser_extract_ipv4_ip(args->output_track_socket_xml, cfgs->snk_tracks_socket->ipAddress);
            parser_extract_ipv4_port(args->output_track_socket_xml, cfgs->snk_tracks_socket->portNumber);
            cfgs->snk_tracks_socket->format = 'x';

            objs->snk_tracks_socket = snk_tracks_socket_construct(cfgs->snk_tracks_socket);

        } 

        if (args->output_track_socket_json != NULL) {

            parser_extract_ipv4_ip(args->output_track_socket_json, cfgs->snk_tracks_socket->ipAddress);
            parser_extract_ipv4_port(args->output_track_socket_json, cfgs->snk_tracks_socket->portNumber);
            cfgs->snk_tracks_socket->format = 'j';

            objs->snk_tracks_socket = snk_tracks_socket_construct(cfgs->snk_tracks_socket);

        } 


    }