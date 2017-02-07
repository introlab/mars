
    #include "objects2objects.h"

    int objects2objects_process(objects * objs, float * processingTime, float * signalTime, unsigned int sampleRate) {

        time_t start, end;
        int rtnValue;

        // Get next hops to process

        if (objs->src_raw_file != NULL) {

            rtnValue = src_raw_file_process(objs->src_raw_file, objs->msg_hops);

        }

        if (rtnValue != 0) {
            return rtnValue;
        }

        // Perform processing       

        start = clock();

        if (objs->mod_ssl != NULL) {
            mod_stft_process(objs->mod_stft, objs->msg_hops, objs->msg_spectra);
            mod_ssl_process(objs->mod_ssl, objs->msg_spectra, objs->msg_pots);    
        }
        
        if (objs->mod_sst != NULL) {
            mod_sst_process(objs->mod_sst, objs->msg_pots, objs->msg_tracks);    
        }

        end = clock();

        // Write results to file

        if (objs->snk_pots != NULL) {
            snk_pots_process(objs->snk_pots, objs->msg_pots);
        }

        if (objs->snk_tracks != NULL) {
            snk_tracks_process(objs->snk_tracks, objs->msg_tracks);
        }

        // Display results in terminal

        // Update times

        *processingTime += ((float) (end-start)) / ((float) CLOCKS_PER_SEC);
        *signalTime += ((float) (objs->msg_hops->hops->array[0]->hopSize)) / ((float) sampleRate);

        return 0;

    }