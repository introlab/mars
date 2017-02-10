    
    #include "objects.h"

    objects * objects_construct_null(void) {

        objects * objs;

        objs = (objects *) malloc(sizeof(objects));

        objs->src_raw_file = (src_raw_file_obj *) NULL;
        objs->msg_hops = (msg_hops_obj *) NULL;
        objs->mod_stft = (mod_stft_obj *) NULL;
        objs->msg_spectra = (msg_spectra_obj *) NULL;
        objs->mod_ssl = (mod_ssl_obj *) NULL;
        objs->msg_pots = (msg_pots_obj *) NULL;
        objs->snk_pots_file = (snk_pots_file_obj *) NULL;
        objs->mod_sst = (mod_sst_obj *) NULL;
        objs->msg_tracks = (msg_tracks_obj *) NULL;
        objs->snk_tracks_file = (snk_tracks_file_obj *) NULL;

        return objs;

    }

    void objects_destroy(objects * objs) {

        if (objs->src_raw_file != NULL) {
            src_raw_file_destroy(objs->src_raw_file);
        }

        if (objs->msg_hops != NULL) {
            msg_hops_destroy(objs->msg_hops);
        }

        if (objs->mod_stft != NULL) {
            mod_stft_destroy(objs->mod_stft);
        }

        if (objs->msg_spectra != NULL) {
            msg_spectra_destroy(objs->msg_spectra);
        }

        if (objs->mod_ssl != NULL) {
            mod_ssl_destroy(objs->mod_ssl);
        }

        if (objs->snk_pots_file != NULL) {
            snk_pots_file_destroy(objs->snk_pots_file);
        }

        if (objs->mod_sst != NULL) {
            //mod_sst_destroy(objs->mod_sst);
        }
        
        if (objs->msg_tracks != NULL) {
            msg_tracks_destroy(objs->msg_tracks);
        }
        
        if (objs->snk_tracks_file != NULL) {
            snk_tracks_file_destroy(objs->snk_tracks_file);
        }

        free((void *) objs);

    }
