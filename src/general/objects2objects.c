
    #include "objects2objects.h"

    int objects2objects_process(objects * objs, float * processingTime, float * signalTime, unsigned int sampleRate) {

        time_t start, end;
        int rtnValue;

        // Get next hops to process

        if (objs->src_raw_file != NULL) {

            rtnValue = src_raw_file_process(objs->src_raw_file, 
                                            objs->msg_hops_raw_in);

        }

        if (objs->src_raw_soundcard != NULL) {

            rtnValue = src_raw_soundcard_process(objs->src_raw_soundcard,
                                                 objs->msg_hops_raw_in);

        }

        if (rtnValue != 0) {
            return rtnValue;
        }

        // Convert hops to good sample rate

        mod_resample_process(objs->mod_resample_raw_in, 
                             objs->msg_hops_raw_in, 
                             objs->msg_hops_raw);

        // Write raw to file

        if (objs->snk_raw_file != NULL) {

            mod_resample_process(objs->mod_resample_raw_out,
                                 objs->msg_hops_raw,
                                 objs->msg_hops_raw_out);

            snk_raw_file_process(objs->snk_raw_file, 
                                 objs->msg_hops_raw_out);

        }

        // Perform processing       

        start = clock();

        if (objs->mod_ssl != NULL) {
            
            mod_stft_process(objs->mod_stft, 
                             objs->msg_hops_raw, 
                             objs->msg_spectra);

            mod_ssl_process(objs->mod_ssl, 
                            objs->msg_spectra, 
                            objs->msg_pots);    

        }
        
        if (objs->mod_sst != NULL) {
            
            mod_sst_process(objs->mod_sst, 
                            objs->msg_pots,
                            objs->msg_tracks);    

        }

        end = clock();

        // Write results to file

        if (objs->snk_pots_file != NULL) {

            snk_pots_file_process(objs->snk_pots_file, 
                                  objs->msg_pots);

        }

        if (objs->snk_tracks_file != NULL) {

            snk_tracks_file_process(objs->snk_tracks_file, 
                                    objs->msg_tracks);

        }

        // Update times

        *processingTime += ((float) (end-start)) / ((float) CLOCKS_PER_SEC);
        *signalTime += ((float) (objs->msg_hops_raw->hops->hopSize)) / ((float) sampleRate);

        return 0;

    }