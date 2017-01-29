
#ifndef __PARAMETERS
#define __PARAMETERS

    #include <mars/mars.h>
    #include <stdlib.h>
    #include <libconfig.h>

    typedef struct parameters_general_obj {

        mics_obj * mics;
        unsigned int hopSize;
        unsigned int frameSize;
        unsigned int fS;
        float c;

    } parameters_general_obj;

    typedef struct parameters_raw_obj {

        unsigned int nBits;

    } parameters_raw_obj;

    typedef struct parameters_ssl_obj {

        unsigned int nPots;
        unsigned int nLevels;
        unsigned int * levels;
        unsigned int * deltasMax;
        unsigned int deltaReset;
        float sigma;
        unsigned int nMatches;
        float epsilon;
        float alpha;
        unsigned int R;
        char * shape;

    } parameters_ssl_obj;    

    typedef struct parameters_sst_obj {

        char * mode;
        unsigned int nTracks;
        float sigmaQ;
        float sigmaR;
        float epsilon;
        unsigned int active_G;
        float * active_weight;
        float * active_mu;
        float * active_sigma;
        unsigned int inactive_G;
        float * inactive_weight;
        float * inactive_mu;
        float * inactive_sigma;
        float Pfalse;
        float Pnew;    
        float Ptrack;
        float theta_new;
        unsigned int N_prob;
        float theta_prob;
        unsigned int * N_inactive;
        float theta_inactive;
        unsigned int nParticles;
        float st_alpha;
        float st_beta;
        float st_ratio;
        float ve_alpha;
        float ve_beta;
        float ve_ratio;
        float ac_alpha;
        float ac_beta;
        float ac_ratio;
        float Nmin;            

    } parameters_sst_obj;       

    typedef struct parameters_obj {

        parameters_general_obj * general;
        parameters_raw_obj * raw;
        parameters_ssl_obj * ssl;
        parameters_sst_obj * sst;    

    } parameters_obj;

    parameters_obj * parameters_construct_file(const char * fileName);

    void parameters_destroy(parameters_obj * obj);

#endif