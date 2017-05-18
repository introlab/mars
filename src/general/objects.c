    
    #include "objects.h"

    objects * objects_construct_null(void) {

        objects * objs;

        objs = (objects *) malloc(sizeof(objects));

        objs->src_raw_file = (src_raw_file_obj *) NULL;
        objs->src_raw_soundcard = (src_raw_soundcard_obj *) NULL;
        objs->src_wav_file = (src_wav_file_obj *) NULL;
        objs->msg_hops_raw_in = (msg_hops_obj *) NULL;
        objs->mod_resample_raw_in = (mod_resample_obj *) NULL;
        objs->msg_hops_raw = (msg_hops_obj *) NULL;
        objs->mod_resample_raw_out = (mod_resample_obj *) NULL;
        objs->msg_hops_raw_out = (msg_hops_obj *) NULL;
        objs->snk_raw_file = (snk_raw_file_obj *) NULL;
        objs->snk_raw_socket = (snk_raw_socket_obj *) NULL;
        objs->mod_stft = (mod_stft_obj *) NULL;
        objs->msg_spectra = (msg_spectra_obj *) NULL;
        objs->snk_spectra_file = (snk_spectra_file_obj *) NULL;
        objs->mod_gcc = (mod_gcc_obj *) NULL;
        objs->msg_xcs = (msg_xcs_obj *) NULL;
        objs->snk_xcs_file = (snk_xcs_file_obj *) NULL;
        objs->mod_ssl = (mod_ssl_obj *) NULL;
        objs->msg_pots = (msg_pots_obj *) NULL;
        objs->snk_pots_file = (snk_pots_file_obj *) NULL;
        objs->snk_pots_socket = (snk_pots_socket_obj *) NULL;
        objs->mod_sst = (mod_sst_obj *) NULL;
        objs->msg_tracks = (msg_tracks_obj *) NULL;
        objs->snk_tracks_file = (snk_tracks_file_obj *) NULL;
        objs->snk_tracks_socket = (snk_tracks_socket_obj *) NULL;

        return objs;

    }

    void objects_destroy(objects * objs) {

        if (objs->src_raw_file != NULL) {
            src_raw_file_destroy(objs->src_raw_file);
        }

        if (objs->msg_hops_raw_in != NULL) {
            msg_hops_destroy(objs->msg_hops_raw_in);
        }

        if (objs->mod_resample_raw_in != NULL) {
            mod_resample_destroy(objs->mod_resample_raw_in);
        }

        if (objs->msg_hops_raw != NULL) {
            msg_hops_destroy(objs->msg_hops_raw);
        }

        if (objs->mod_resample_raw_out != NULL) {
            mod_resample_destroy(objs->mod_resample_raw_out);
        }

        if (objs->msg_hops_raw_out != NULL) {
            msg_hops_destroy(objs->msg_hops_raw_out);
        }

        if (objs->snk_raw_file != NULL) {
            snk_raw_file_destroy(objs->snk_raw_file);
        }

        if (objs->mod_stft != NULL) {
            mod_stft_destroy(objs->mod_stft);
        }

        if (objs->msg_spectra != NULL) {
            msg_spectra_destroy(objs->msg_spectra);
        }

        if (objs->snk_spectra_file != NULL) {
            snk_spectra_file_destroy(objs->snk_spectra_file);
        }

        if (objs->mod_gcc != NULL) {
            mod_gcc_destroy(objs->mod_gcc);
        }

        if (objs->msg_xcs != NULL) {
            msg_xcs_destroy(objs->msg_xcs);
        }

        if (objs->snk_xcs_file != NULL) {
            snk_xcs_file_destroy(objs->snk_xcs_file);
        }

        if (objs->mod_ssl != NULL) {
            mod_ssl_destroy(objs->mod_ssl);
        }

        if (objs->msg_pots != NULL) {
            msg_pots_destroy(objs->msg_pots);
        }

        if (objs->snk_pots_file != NULL) {
            snk_pots_file_destroy(objs->snk_pots_file);
        }

        if (objs->snk_pots_socket != NULL) {
            snk_pots_socket_destroy(objs->snk_pots_socket);
        }       

        if (objs->mod_sst != NULL) {
            mod_sst_destroy(objs->mod_sst);
        }
        
        if (objs->msg_tracks != NULL) {
            msg_tracks_destroy(objs->msg_tracks);
        }
        
        if (objs->snk_tracks_file != NULL) {
            snk_tracks_file_destroy(objs->snk_tracks_file);
        }

        if (objs->snk_tracks_socket != NULL) {
            snk_tracks_socket_destroy(objs->snk_tracks_socket);
        }

        free((void *) objs);

    }
