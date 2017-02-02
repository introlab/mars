
    #include <mars/mars.h>

    #include <getopt.h>

    #include "parameters/parameters.h"
    #include "parameters/parameters2config.h"

    int main(int argc, char* argv[])
    {
    
        FILE * fp;

        time_t start, end;
        float totalTime;
        unsigned int nHops;

        float signalDuration, processingDuration;    

        struct objects {

            src_raw_obj * src_raw;
            msg_hops_obj * msg_hops;
            mod_stft_obj * mod_stft;
            msg_spectra_obj * msg_spectra;
            mod_ssl_obj * mod_ssl;
            msg_pots_obj * msg_pots;
            snk_pots_obj * snk_pots;
            mod_sst_obj * mod_sst;
            msg_tracks_obj * msg_tracks;
            snk_tracks_obj * snk_tracks;

        } objects;

        struct configs {

            src_raw_cfg * src_raw;
            msg_hops_cfg * msg_hops;
            mod_stft_cfg * mod_stft;
            msg_spectra_cfg * msg_spectra;
            mod_ssl_cfg * mod_ssl;
            msg_pots_cfg * msg_pots;
            snk_pots_cfg * snk_pots;
            mod_sst_cfg * mod_sst;
            msg_tracks_cfg * msg_tracks;
            snk_tracks_cfg * snk_tracks;

        } configs;

        // Parsing arguments
        int c;
        char * cValue = NULL;
        char * rValue = NULL;
        char * pValue = NULL;
        char * tValue = NULL;

        // Parameters
        parameters_obj * parameters;

	    while ((c = getopt(argc,argv, "c:r:p:t:")) != -1) {

	        switch(c) {

	            case 'c':
	                cValue = optarg;
	            break;
	            case 'r':
	                rValue = optarg;
	            break;
	            case 'p':
	                pValue = optarg;
	            break;
                case 't':
                    tValue = optarg;
                break;
	            default:
	                exit(EXIT_FAILURE);

	        }

	    }

	    if (cValue == NULL) { printf("Missing configuration file.\n"); exit(EXIT_FAILURE); }
	    if (rValue == NULL) { printf("Missing input.\n"); exit(EXIT_FAILURE); }

        // Load parameters from file
        parameters = parameters_construct_file(cValue);
        
        // Load configurations
        configs.src_raw = parameters2src_raw(parameters);
        configs.msg_hops = parameters2msg_hops(parameters);
        configs.mod_stft = parameters2mod_stft(parameters);
        configs.msg_spectra = parameters2msg_spectra(parameters);
        configs.mod_ssl = parameters2mod_ssl(parameters);
        configs.msg_pots = parameters2msg_pots(parameters);
        configs.snk_pots = parameters2snk_pots(parameters);
        configs.mod_sst = parameters2mod_sst(parameters);
        configs.msg_tracks = parameters2msg_tracks(parameters);
        configs.snk_tracks = parameters2snk_tracks(parameters);        

        // Copy file name of the RAW file
        strcpy(configs.src_raw->fileName,rValue);

        // Copy file name of the potential sources
        if (pValue != NULL) {
            strcpy(configs.snk_pots->fileName,pValue);
            strcpy(configs.snk_pots->format,"bin");
        }

        // Copy file name of the tracked sources
        if (tValue != NULL) {
            strcpy(configs.snk_tracks->fileName,tValue);
            strcpy(configs.snk_tracks->format,"bin");
        }

        // Instantiate objects
        objects.src_raw = src_raw_construct(configs.src_raw);
        objects.msg_hops = msg_hops_construct(configs.msg_hops);
        objects.mod_stft = mod_stft_construct(configs.mod_stft);
        objects.msg_spectra = msg_spectra_construct(configs.msg_spectra);
        objects.mod_ssl = mod_ssl_construct(configs.mod_ssl);
        objects.msg_pots = msg_pots_construct(configs.msg_pots);
        objects.mod_sst = mod_sst_construct(configs.mod_sst);
        objects.msg_tracks = msg_tracks_construct(configs.msg_tracks);

        if (pValue != NULL) {
            objects.snk_pots = snk_pots_construct(configs.snk_pots);    
        }
        if (tValue != NULL) {
            objects.snk_tracks = snk_tracks_construct(configs.snk_tracks);
        }
        
        // Processing
        printf("Processing... "); fflush(stdout);

        nHops = 0;
        while(src_raw_process(objects.src_raw, objects.msg_hops) == 0) {
            
            //printf("%u\n",nHops);

            start = clock();

            mod_stft_process(objects.mod_stft, objects.msg_hops, objects.msg_spectra);
            mod_ssl_process(objects.mod_ssl, objects.msg_spectra, objects.msg_pots);
            mod_sst_process(objects.mod_sst, objects.msg_pots, objects.msg_tracks);

            end = clock();

            nHops++;

            totalTime += (float) (end-start);

            if (pValue != NULL) {
                snk_pots_process(objects.snk_pots, objects.msg_pots);    
            }      
            if (tValue != NULL) {
                snk_tracks_process(objects.snk_tracks, objects.msg_tracks);
            }             

        }

        printf("[Done]\n");

        // Free objects
        src_raw_destroy(objects.src_raw);
        msg_hops_destroy(objects.msg_hops);
        mod_stft_destroy(objects.mod_stft);
        msg_spectra_destroy(objects.msg_spectra);
        mod_ssl_destroy(objects.mod_ssl);
        msg_pots_destroy(objects.msg_pots);
        mod_sst_destroy(objects.mod_sst);
        msg_tracks_destroy(objects.msg_tracks);

        if (pValue != NULL) {
            snk_pots_destroy(objects.snk_pots);
        }
        if (tValue != NULL) {
            snk_tracks_destroy(objects.snk_tracks);
        }

        // Free configurations
        src_raw_cfg_destroy(configs.src_raw);
        msg_hops_cfg_destroy(configs.msg_hops);
        mod_stft_cfg_destroy(configs.mod_stft);
        msg_spectra_cfg_destroy(configs.msg_spectra);
        mod_ssl_cfg_destroy(configs.mod_ssl);
        msg_pots_cfg_destroy(configs.msg_pots);
        snk_pots_cfg_destroy(configs.snk_pots);
        mod_sst_cfg_destroy(configs.mod_sst);
        msg_tracks_cfg_destroy(configs.msg_tracks);
        snk_tracks_cfg_destroy(configs.snk_tracks);

        // Load parameters from file
        parameters_destroy(parameters);
        
        signalDuration = ((float) nHops) * ((float) (parameters->general->hopSize)) / parameters->general->fS;
        processingDuration = (totalTime/((float) CLOCKS_PER_SEC));

        printf("Signal duration: %1.3f secs\n",signalDuration);
        printf("Processing duration: %1.3f secs\n",processingDuration);
        printf("CPU usage: %2.3f%%\n", 100.0f*processingDuration/signalDuration);

        return 0;

    }