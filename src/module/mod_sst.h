#ifndef __MARS_MODULE_SST
#define __MARS_MODULE_SST
  
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include <math.h>

    #include "../signal/kalman.h"
    #include "../system/kalman2kalman.h"

    #include "../signal/particle.h"
    #include "../system/particle2particle.h"

    #include "../signal/coherence.h"
    #include "../system/kalman2coherence.h"
    #include "../system/particle2coherence.h"

    #include "../signal/mixture.h"
    #include "../system/mixture2mixture.h"

    #include "../message/msg_pots.h"
    #include "../message/msg_tracks.h"

    typedef struct mod_sst_obj {

        unsigned int nPots;
        unsigned int nTracksMax;
        unsigned int nTracks;

        char * mode;

        mixture_obj ** mixtures;
        coherences_obj ** coherences;
        postprobs_obj ** postprobs;

        unsigned long long * ids;
        unsigned long long * idsAdded;
        unsigned long long * idsRemoved;
        
        char * type;

        kalman_obj ** kalmans;
        kalman2kalman_obj * kalman2kalman_prob;
        kalman2kalman_obj * kalman2kalman_active;
        kalman2coherence_obj * kalman2coherence_prob;
        kalman2coherence_obj * kalman2coherence_active;
        
        particles_obj ** particles;
        particle2particle_obj * particle2particle_prob;
        particle2particle_obj * particle2particle_active;
        particle2coherence_obj * particle2coherence_prob;
        particle2coherence_obj * particle2coherence_active;

        mixture2mixture_obj * mixture2mixture;
        
        float theta_new;
        unsigned int N_prob;
        float theta_prob;
        unsigned int * N_inactive;
        float theta_inactive;

        unsigned int * n_prob;
        float * mean_prob;
        unsigned int * n_inactive;

        unsigned long long id;

    } mod_sst_obj;

    typedef struct mod_sst_cfg {

        unsigned int nPots;
        unsigned int nTracks;

        char * mode;

        unsigned int R;
        unsigned int hopSize;
        unsigned int fS;
        float sigmaQ;
        
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

        float epsilon;
        float sigmaR_active;
        float sigmaR_prob;
        gaussians_1d_obj * active_gmm;
        gaussians_1d_obj * inactive_gmm;
        float Pfalse;
        float Pnew;
        float Ptrack;
        char * shape;

        float theta_new;
        unsigned int N_prob;
        float theta_prob;
        unsigned int * N_inactive;
        float theta_inactive;

    } mod_sst_cfg;

    mod_sst_obj * mod_sst_construct(const mod_sst_cfg * cfg);

    void mod_sst_destroy(mod_sst_obj * obj);

    void mod_sst_process(mod_sst_obj * obj, const msg_pots_obj * msg_pots, msg_tracks_obj * msg_tracks);

    mod_sst_cfg * mod_sst_cfg_construct(void);

    void mod_sst_cfg_destroy(mod_sst_cfg * cfg);

#endif