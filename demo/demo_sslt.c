#include <mars/mars.h>

#include <stdio.h>
#include <libconfig.h>
#include <getopt.h>

struct objects {

    src_raw_obj * src_raw;
    msg_hops_obj * msg_hops;
    stft_obj * stft;
    msg_spectra_obj * msg_spectra;
    ssl_obj * ssl;
    msg_pots_obj * msg_pots;
    snk_pots_obj * snk_pots;

} objects;

struct parameters {

    struct general {
        matrix_float * mics;
        unsigned int hopSize;
        unsigned int frameSize;
        unsigned int fS;
        float c;
    } general;

    struct raw {      
        unsigned int nBits;
    } raw ;

    struct ssl {
        vector_unsignedint * levels;
        vector_unsignedint * deltas;
        double sigma;
        unsigned int nMatches;
        double epsilon;
    } ssl;

} parameters;

int configuration_load(const char * fileName) {

    config_t cfg;
    config_setting_t * setting;
    int i;
    int N;
    int valueInt;
    double valueDouble;

    config_init(&cfg);

    /* Read the file. If there is an error, report it and exit. */
    if(!config_read_file(&cfg, fileName))
    {
        
        printf("%s:%d - %s\n", config_error_file(&cfg), config_error_line(&cfg), config_error_text(&cfg));
        config_destroy(&cfg);
      
        exit(EXIT_FAILURE);

    }     

    // General

    if (config_lookup_int(&cfg, "general.hopSize", &valueInt)) {
        parameters.general.hopSize = valueInt;
    }
    else {
        printf("Missing: general.hopSize\n");
        exit(EXIT_FAILURE);
    }
    
    if (config_lookup_int(&cfg, "general.frameSize", &valueInt)) {
        parameters.general.frameSize = valueInt;
    }
    else {
        printf("Missing: general.frameSize\n");
        exit(EXIT_FAILURE);        
    }

    if (config_lookup_int(&cfg, "general.fS", &valueInt)) {
        parameters.general.fS = valueInt;
    }
    else {
        printf("Missing: general.fS\n");
        exit(EXIT_FAILURE);
    }
    
    if (config_lookup_float(&cfg, "general.c", &valueDouble)) {
        parameters.general.c = (float) valueDouble;
    }
    else {
        printf("Missing: general.c\n");
        exit(EXIT_FAILURE);        
    }

    setting = config_lookup(&cfg, "general.mics");

    if (setting != NULL) {

        N = config_setting_length(setting);

        parameters.general.mics = matrix_float_malloc(N,3);

        for (i = 0; i < N; i++) {

            config_setting_lookup_float(config_setting_get_elem(setting, i),"x",&valueDouble);
            parameters.general.mics->array[i][0] = (float) valueDouble;
            config_setting_lookup_float(config_setting_get_elem(setting, i),"y",&valueDouble);
            parameters.general.mics->array[i][1] = (float) valueDouble;
            config_setting_lookup_float(config_setting_get_elem(setting, i),"z",&valueDouble);
            parameters.general.mics->array[i][2] = (float) valueDouble;

        }

    }
    else {
        
        printf("Missing: general.mics\n"); exit(EXIT_FAILURE);

    }

    // Raw

    if (config_lookup_int(&cfg, "raw.nBits", &valueInt)) {
        parameters.raw.nBits = valueInt;
    }
    else {
        printf("Missing: raw.nBits\n");
        exit(EXIT_FAILURE);
    }

    // SSL

    if (config_lookup_float(&cfg, "ssl.sigma", &valueDouble)) {
        parameters.ssl.sigma = (float) valueDouble;
    }
    else {
        printf("Missing: ssl.sigma\n");
        exit(EXIT_FAILURE);        
    }    

    if (config_lookup_int(&cfg, "ssl.nMatches", &valueInt)) {
        parameters.ssl.nMatches = (float) valueInt;
    }
    else {
        printf("Missing: ssl.nMatches\n");
        exit(EXIT_FAILURE);        
    }    

    if (config_lookup_float(&cfg, "ssl.epsilon", &valueDouble)) {
        parameters.ssl.epsilon = (float) valueDouble;
    }
    else {
        printf("Missing: ssl.epsilon\n");
        exit(EXIT_FAILURE);        
    }    

    setting = config_lookup(&cfg, "ssl.levels");

    if (setting != NULL) {

        N = config_setting_length(setting);

        parameters.ssl.levels = vector_unsignedint_malloc(N);

        for (i = 0; i < N; i++) {

            valueInt = config_setting_get_int_elem(setting, i);
            parameters.ssl.levels->array[i] = valueInt;

        }

    }
    else {
        
        printf("Missing: ssl.levels\n"); exit(EXIT_FAILURE);

    }


    setting = config_lookup(&cfg, "ssl.deltas");

    if (setting != NULL) {

        N = config_setting_length(setting);

        parameters.ssl.deltas = vector_unsignedint_malloc(N);

        for (i = 0; i < N; i++) {

            valueInt = config_setting_get_int_elem(setting, i);
            parameters.ssl.deltas->array[i] = valueInt;

        }

    }
    else {
        
        printf("Missing: ssl.deltas\n"); exit(EXIT_FAILURE);

    }    

    config_destroy(&cfg);

}

int configuration_free(void) {

    matrix_float_free(parameters.general.mics);
    vector_unsignedint_free(parameters.ssl.levels);
    vector_unsignedint_free(parameters.ssl.deltas);

}

int main(int argc, char* argv[])
{

    time_t start, end;
    float totalTime;
    unsigned int nHops;

    float signalDuration, processingDuration;    

    // Parsing arguments
    int c;
    char * cValue = NULL;
    char * rValue = NULL;
    char * pValue = NULL;

    while ((c = getopt(argc,argv, "c:r:p:")) != -1) {

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
            default:
                exit(EXIT_FAILURE);

        }

    }

    if (cValue == NULL) { printf("Missing configuration file.\n"); exit(EXIT_FAILURE); }
    if (rValue == NULL) { printf("Missing input.\n"); exit(EXIT_FAILURE); }

    // Configuration

    configuration_load(cValue);

    // Initialize objects

    objects.src_raw = src_raw_construct(parameters.general.hopSize,
                                        parameters.general.mics->nRows,
                                        parameters.raw.nBits,
                                        rValue);

    objects.msg_hops = msg_hops_construct(parameters.general.hopSize,
                                          parameters.general.frameSize);

    objects.stft = stft_construct(parameters.general.hopSize,
                                  parameters.general.frameSize,
                                  parameters.general.mics->nRows);

    objects.msg_spectra = msg_spectra_construct(parameters.general.frameSize,
                                                parameters.general.mics->nRows);

    objects.ssl = ssl_construct(parameters.general.mics,
                                parameters.general.frameSize,
                                parameters.general.fS,
                                parameters.general.c,
                                parameters.ssl.levels,
                                parameters.ssl.deltas,
                                parameters.ssl.sigma,
                                parameters.ssl.nMatches,
                                parameters.ssl.epsilon);

    objects.msg_pots = msg_pots_construct();

    if (pValue != NULL) {
        objects.snk_pots = snk_pots_construct(pValue, "bin");
    }

    // Process

    totalTime = 0.0f;
    nHops = 0;

    printf("Processing... "); fflush(stdout);

    while(src_raw_process(objects.src_raw, objects.msg_hops) == 0) {

        start = clock();

        stft_process(objects.stft, objects.msg_hops, objects.msg_spectra);
        ssl_process(objects.ssl, objects.msg_spectra, objects.msg_pots);

        end = clock();

        totalTime += (float) (end-start);

        if (pValue != NULL) {
            snk_pots_process(objects.snk_pots, objects.msg_pots);
        }

        nHops++;

    }

    printf("[Done]\n");

    // Configuration

    configuration_free();

    // Free memory

    src_raw_destroy(objects.src_raw);

    msg_hops_destroy(objects.msg_hops);

    stft_destroy(objects.stft);

    msg_spectra_destroy(objects.msg_spectra);

    ssl_destroy(objects.ssl);

    msg_pots_destroy(objects.msg_pots);

    if (pValue != NULL) {
        snk_pots_destroy(objects.snk_pots);
    }

    // Statistics

    signalDuration = ((float) (nHops*parameters.general.hopSize)) / (parameters.general.fS);
    processingDuration = (totalTime/((float) CLOCKS_PER_SEC));

    printf("Signal duration: %2.3f sec\n", signalDuration);
    printf("Processing time: %2.3f sec\n", processingDuration);
    printf("CPU usage: %2.3f%%\n", 100.0f*processingDuration/signalDuration);
   
    return 0;
}