    
    #include "mod_sst.h"

    mod_sst_obj * mod_sst_construct(const mod_sst_cfg * cfg) {

        mod_sst_obj * obj;
        unsigned int iTrackMax;
        float deltaT;
        float diffuse_cst;

        obj = (mod_sst_obj *) malloc(sizeof(mod_sst_obj));

        obj->nPots = cfg->nPots;
        obj->nTracksMax = cfg->nTracks;
        obj->nTracks = 0;

        obj->mode = (char *) malloc(sizeof(char) * (strlen(cfg->mode) + 1));
        strcpy(obj->mode, cfg->mode);

        obj->mixtures = (mixture_obj **) malloc(sizeof(mixture_obj *) * (obj->nTracksMax+1));
        obj->coherences = (coherences_obj **) malloc(sizeof(coherences_obj *) * (obj->nTracksMax+1));
        obj->postprobs = (postprobs_obj **) malloc(sizeof(postprobs_obj *) * (obj->nTracksMax+1));

        for (iTrackMax = 0; iTrackMax <= obj->nTracksMax; iTrackMax++) {

            obj->mixtures[iTrackMax] = mixture_construct_zero(obj->nPots, iTrackMax);
            obj->coherences[iTrackMax] = coherences_construct_zero(obj->nPots, iTrackMax);
            obj->postprobs[iTrackMax] = postprobs_construct_zero(obj->nPots, iTrackMax); 

        }

        obj->ids = (unsigned long long *) malloc(sizeof(unsigned long long) * obj->nTracksMax);
        obj->idsAdded = (unsigned long long *) malloc(sizeof(unsigned long long) * obj->nTracksMax);
        obj->idsRemoved = (unsigned long long *) malloc(sizeof(unsigned long long) * obj->nTracksMax);
                
        obj->type = (char *) malloc(sizeof(char) * obj->nTracksMax);
        
        obj->kalmans = (kalman_obj **) malloc(sizeof(kalman_obj *) * obj->nTracksMax); 
        memset(obj->kalmans, 0x00, sizeof(kalman_obj *) * obj->nTracksMax);
        obj->particles = (particles_obj **) malloc(sizeof(particles_obj *) * obj->nTracksMax);
        memset(obj->particles, 0x00, sizeof(particles_obj *) * obj->nTracksMax);
        
        obj->theta_new = cfg->theta_new;
        obj->N_prob = cfg->N_prob;
        obj->theta_prob = cfg->theta_prob;
        obj->N_inactive = (unsigned int *) malloc(sizeof(unsigned int) * obj->nTracksMax);

        obj->theta_inactive = cfg->theta_inactive;

        obj->n_prob = (unsigned int *) malloc(sizeof(unsigned int) * obj->nTracksMax);
        obj->mean_prob = (float *) malloc(sizeof(float) * obj->nTracksMax);
        obj->n_inactive = (unsigned int *) malloc(sizeof(unsigned int) * obj->nTracksMax);

        for (iTrackMax = 0; iTrackMax < obj->nTracksMax; iTrackMax++) {

            obj->ids[iTrackMax] = 0;
            obj->idsAdded[iTrackMax] = 0;
            obj->idsRemoved[iTrackMax] = 0;

            obj->type[iTrackMax] = 'I';

            if (strcmp(obj->mode, "kalman") == 0) {
                obj->kalmans[iTrackMax] =  kalman_construct_zero();    
            }
            else {
                obj->particles[iTrackMax] =  particles_construct_zero(cfg->nParticles);       
            }
            
            obj->N_inactive[iTrackMax] = cfg->N_inactive[iTrackMax];

            obj->n_prob[iTrackMax] = 0;
            obj->mean_prob[iTrackMax] = 0.0f;
            obj->n_inactive[iTrackMax] = 0;

        }       

        if (strcmp(cfg->shape,"arc") == 0) {
            diffuse_cst = 1.0f / (M_PI);
        }
        else if (strcmp(cfg->shape,"halfsphere") == 0) {
            diffuse_cst = 1.0f / (2*M_PI);
        }
        else {
            diffuse_cst = 1.0f / (4*M_PI);
        }

        deltaT = ((float) (cfg->R * cfg->hopSize)) / ((float) cfg->fS);
        
        if (strcmp(obj->mode, "kalman") == 0) {

            obj->kalman2kalman_prob = kalman2kalman_construct(deltaT,
                                                              cfg->sigmaQ,
                                                              cfg->sigmaR_prob,
                                                              cfg->epsilon);    

            obj->kalman2kalman_active = kalman2kalman_construct(deltaT,
                                                                cfg->sigmaQ,
                                                                cfg->sigmaR_active,
                                                                cfg->epsilon);    

            obj->kalman2coherence_prob = kalman2coherence_construct(cfg->epsilon, 
                                                                    cfg->sigmaR_prob);

            obj->kalman2coherence_active = kalman2coherence_construct(cfg->epsilon, 
                                                                      cfg->sigmaR_active);

            obj->particle2particle_prob = NULL;
            obj->particle2particle_active = NULL;
            obj->particle2coherence_prob = NULL;
            obj->particle2coherence_active = NULL;

        }
        else {

            obj->kalman2kalman_prob = NULL;
            obj->kalman2kalman_active = NULL;
            obj->kalman2coherence_prob = NULL;
            obj->kalman2coherence_active = NULL;

            obj->particle2particle_prob = particle2particle_construct(cfg->nParticles,
                                                                      deltaT,
                                                                      cfg->st_alpha,
                                                                      cfg->st_beta,
                                                                      cfg->st_ratio,
                                                                      cfg->ve_alpha,
                                                                      cfg->ve_beta,
                                                                      cfg->ve_ratio,
                                                                      cfg->ac_alpha,
                                                                      cfg->ac_beta,
                                                                      cfg->ac_ratio,
                                                                      (double) cfg->epsilon,
                                                                      cfg->sigmaR_prob,
                                                                      cfg->Nmin);

            obj->particle2particle_active = particle2particle_construct(cfg->nParticles,
                                                                        deltaT,
                                                                        cfg->st_alpha,
                                                                        cfg->st_beta,
                                                                        cfg->st_ratio,
                                                                        cfg->ve_alpha,
                                                                        cfg->ve_beta,
                                                                        cfg->ve_ratio,
                                                                        cfg->ac_alpha,
                                                                        cfg->ac_beta,
                                                                        cfg->ac_ratio,
                                                                        (double) cfg->epsilon,
                                                                        cfg->sigmaR_active,
                                                                        cfg->Nmin);    

            obj->particle2coherence_prob = particle2coherence_construct(cfg->sigmaR_prob);

            obj->particle2coherence_active = particle2coherence_construct(cfg->sigmaR_active);

        }


        obj->mixture2mixture = mixture2mixture_construct(cfg->active_gmm,
                                                         cfg->inactive_gmm,
                                                         diffuse_cst,
                                                         cfg->Pfalse,
                                                         cfg->Pnew,
                                                         cfg->Ptrack,
                                                         cfg->epsilon);

        obj->id = 0;

        return obj;

    }

    void mod_sst_destroy(mod_sst_obj * obj) {

        unsigned int iTrackMax;

        free((void *) obj->mode);

        for (iTrackMax = 0; iTrackMax <= obj->nTracksMax; iTrackMax++) {

            mixture_destroy(obj->mixtures[iTrackMax]);
            coherences_destroy(obj->coherences[iTrackMax]);
            postprobs_destroy(obj->postprobs[iTrackMax]);

        }

        for (iTrackMax = 0; iTrackMax < obj->nTracksMax; iTrackMax++) {

            if (obj->kalmans[iTrackMax] != NULL) {

                kalman_destroy(obj->kalmans[iTrackMax]);

            }

            if (obj->particles[iTrackMax] != NULL) {

                particles_destroy(obj->particles[iTrackMax]);

            }

        }

        free((void *) obj->mixtures);
        free((void *) obj->coherences);
        free((void *) obj->postprobs);

        free((void *) obj->ids);
        free((void *) obj->idsAdded);
        free((void *) obj->idsRemoved);
        free((void *) obj->type);

        free((void *) obj->kalmans);
        free((void *) obj->particles);

        free((void *) obj->N_inactive);
        free((void *) obj->n_prob);
        free((void *) obj->mean_prob);
        free((void *) obj->n_inactive);

        if (obj->kalman2kalman_prob != NULL) {
            kalman2kalman_destroy(obj->kalman2kalman_prob);
        }
        if (obj->kalman2kalman_active != NULL) {
            kalman2kalman_destroy(obj->kalman2kalman_active);
        }
        if (obj->kalman2coherence_prob != NULL) {
            kalman2coherence_destroy(obj->kalman2coherence_prob);
        }
        if (obj->kalman2coherence_active != NULL) {
            kalman2coherence_destroy(obj->kalman2coherence_active);
        }
        if (obj->particle2particle_prob != NULL) {
            particle2particle_destroy(obj->particle2particle_prob);
        }
        if (obj->particle2particle_active != NULL) {
            particle2particle_destroy(obj->particle2particle_active);
        }
        if (obj->particle2coherence_prob != NULL)  {
            particle2coherence_destroy(obj->particle2coherence_prob);
        }
        if (obj->particle2coherence_active != NULL)  {
            particle2coherence_destroy(obj->particle2coherence_active);
        }

    }

    void mod_sst_process(mod_sst_obj * obj, const msg_pots_obj * msg_pots, msg_tracks_obj * msg_tracks) {

        unsigned int iPot;
        unsigned int iTrackMax;
        unsigned int iTrack;
        float x,y,z;
        float sourceActivity;

        // Count

        obj->nTracks = 0;

        for (iTrackMax = 0; iTrackMax < obj->nTracksMax; iTrackMax++) {

            if (obj->ids[iTrackMax] != 0) {

                obj->nTracks++;

            }

        }

        // Predict  

        for (iTrackMax = 0; iTrackMax < obj->nTracksMax; iTrackMax++) {

            if (obj->ids[iTrackMax] != 0) {

                if (strcmp(obj->mode,"kalman") == 0) {

                    switch (obj->type[iTrackMax]) {
                        
                        case 'P':                    

                            kalman2kalman_predict(obj->kalman2kalman_prob,
                                                  obj->kalmans[iTrackMax]);         

                        break;

                        case 'A':

                            kalman2kalman_predict(obj->kalman2kalman_active,
                                                  obj->kalmans[iTrackMax]);  

                        break;

                        default:

                            printf("Unknown state.\n");
                            exit(EXIT_FAILURE);                        

                        break;

                    }

                }
                else {

                    switch (obj->type[iTrackMax]) {
                        
                        case 'P':    

                            particle2particle_predict(obj->particle2particle_prob,
                                                      obj->particles[iTrackMax]);                        

                        break;

                        case 'A':

                            particle2particle_predict(obj->particle2particle_active,
                                                      obj->particles[iTrackMax]);                        

                        break;

                        default:

                            printf("Unknown state.\n");
                            exit(EXIT_FAILURE);                        

                        break;

                    }                        

                }


            }

        }

        // Coherence

        iTrack = 0;

        for (iTrackMax = 0; iTrackMax < obj->nTracksMax; iTrackMax++) {

            if (obj->ids[iTrackMax] != 0) {

                if (strcmp(obj->mode,"kalman") == 0) {

                    switch (obj->type[iTrackMax]) {
                        
                        case 'P':  

                            kalman2coherence_process(obj->kalman2coherence_prob,
                                                     obj->kalmans[iTrackMax],
                                                     msg_pots->pots,
                                                     iTrack,
                                                     obj->coherences[obj->nTracks]);

                        break;

                        case 'A':

                            kalman2coherence_process(obj->kalman2coherence_active,
                                                     obj->kalmans[iTrackMax],
                                                     msg_pots->pots,
                                                     iTrack,
                                                     obj->coherences[obj->nTracks]);

                        break;

                        default:

                            printf("Unknown state.\n");
                            exit(EXIT_FAILURE);                            

                        break;

                    }

                }
                else {

                    switch (obj->type[iTrackMax]) {
                        
                        case 'P':                      

                            particle2coherence_process(obj->particle2coherence_prob,
                                                       obj->particles[iTrackMax],
                                                       msg_pots->pots,
                                                       iTrack,
                                                       obj->coherences[obj->nTracks]);

                        break;

                        case 'A':                      

                            particle2coherence_process(obj->particle2coherence_active,
                                                       obj->particles[iTrackMax],
                                                       msg_pots->pots,
                                                       iTrack,
                                                       obj->coherences[obj->nTracks]);

                        break;

                        default:

                            printf("Unknown state.\n");
                            exit(EXIT_FAILURE);                            

                        break;                        

                    }

                }

                iTrack++;

            }

        }

        // Mixture

        mixture2mixture_process(obj->mixture2mixture, 
        	                    obj->mixtures[obj->nTracks], 
        	                    msg_pots->pots, 
        	                    obj->coherences[obj->nTracks], 
        	                    obj->postprobs[obj->nTracks]);

        // Update

        iTrack = 0;

        for (iTrackMax = 0; iTrackMax < obj->nTracksMax; iTrackMax++) {

            if (obj->ids[iTrackMax] != 0) {

                if (strcmp(obj->mode,"kalman") == 0) {

                    switch (obj->type[iTrackMax]) {
                        
                        case 'P':                                                  

                            kalman2kalman_update(obj->kalman2kalman_prob,
                                                 obj->postprobs[obj->nTracks],
                                                 iTrack,
                                                 msg_pots->pots,
                                                 obj->kalmans[iTrackMax]);

                        break;

                        case 'A':                      

                            kalman2kalman_update(obj->kalman2kalman_active,
                                                 obj->postprobs[obj->nTracks],
                                                 iTrack,
                                                 msg_pots->pots,
                                                 obj->kalmans[iTrackMax]);

                        break;

                        default:

                            printf("Unknown state.\n");
                            exit(EXIT_FAILURE); 

                        break;

                    }

                }
                else {

                    switch (obj->type[iTrackMax]) {
                        
                        case 'P':                      

                            particle2particle_update(obj->particle2particle_prob,
                                                     obj->postprobs[obj->nTracks],
                                                     iTrack,
                                                     msg_pots->pots,
                                                     obj->particles[iTrackMax]);

                        break;

                        case 'A':

                            particle2particle_update(obj->particle2particle_active,
                                                     obj->postprobs[obj->nTracks],
                                                     iTrack,
                                                     msg_pots->pots,
                                                     obj->particles[iTrackMax]);

                        break;

                        default:

                            printf("Unknown state.\n");
                            exit(EXIT_FAILURE);                         

                        break;

                    }

                }

                iTrack++;

            }

        }

        // Activity

        iTrack = 0;

        for (iTrackMax = 0; iTrackMax < obj->nTracksMax; iTrackMax++) {

            if (obj->ids[iTrackMax] != 0) {

                sourceActivity = obj->postprobs[obj->nTracks]->arrayTrackTotal[iTrack];

                // Update counters
                
                switch (obj->type[iTrackMax]) {
                    
                    case 'P':

                        obj->n_prob[iTrackMax]++;
                        obj->mean_prob[iTrackMax] += sourceActivity;

                    break;

                    case 'A':

                        if (sourceActivity >= obj->theta_inactive) {
                            obj->n_inactive[iTrackMax] = 0;
                        }
                        else {
                            obj->n_inactive[iTrackMax]++;   
                        }

                    break;

                    default:

                        printf("Unknown state.\n");
                        exit(EXIT_FAILURE);

                    break;

                }

                iTrack++;

            }

        }        

        // Transitions

        iTrack = 0;

        for (iTrackMax = 0; iTrackMax < obj->nTracksMax; iTrackMax++) {

            if (obj->ids[iTrackMax] != 0) {

                if ((obj->type[iTrackMax] == 'P') && 
                    (obj->n_prob[iTrackMax] == obj->N_prob) && 
                    (obj->mean_prob[iTrackMax]/((float) obj->N_prob) >= obj->theta_prob)) {

                    obj->type[iTrackMax] = 'A';
                    obj->n_inactive[iTrackMax] = 0;

                }

                iTrack++;

            }

        }          

        // Add source
        
        for (iTrackMax = 0; iTrackMax < obj->nTracksMax; iTrackMax++) {

            obj->idsAdded[iTrackMax] = 0;

        }

        for (iPot = 0; iPot < obj->nPots; iPot++) {

            if (obj->postprobs[obj->nTracks]->arrayNew[iPot] > obj->theta_new) {                

                for (iTrackMax = 0; iTrackMax < obj->nTracksMax; iTrackMax++) {

                    if (obj->ids[iTrackMax] == 0) {

                        obj->id++;
                        obj->idsAdded[iTrackMax] = obj->id;
                        
                        if (strcmp(obj->mode,"kalman") == 0) {

                            kalman2kalman_init(obj->kalman2kalman_prob, 
                                               msg_pots->pots,
                                               iPot, 
                                               obj->kalmans[iTrackMax]); 

                        }
                        else {

                            particle2particle_init(obj->particle2particle_prob, 
                                                   msg_pots->pots,
                                                   iPot, 
                                                   obj->particles[iTrackMax]);

                        }
                        
                        obj->type[iTrackMax] = 'P';
                        obj->n_prob[iTrackMax] = 0;
                        obj->mean_prob[iTrackMax] = 0.0f;

                        break;

                    }

                }

            }

        }

        // Remove source

        for (iTrackMax = 0; iTrackMax < obj->nTracksMax; iTrackMax++) {

            obj->idsRemoved[iTrackMax] = 0;
            
        }

        iTrack = 0;

        for (iTrackMax = 0; iTrackMax < obj->nTracksMax; iTrackMax++) {

            if (obj->ids[iTrackMax] != 0) {

                if ((obj->type[iTrackMax] == 'P') && 
                    (obj->n_prob[iTrackMax] == obj->N_prob) && 
                    (obj->mean_prob[iTrackMax]/((float) obj->N_prob) < obj->theta_prob)) {

                    obj->idsRemoved[iTrackMax] = obj->ids[iTrackMax];

                }

                if ((obj->type[iTrackMax] == 'A') &&
                    (obj->n_inactive[iTrackMax] >= obj->N_inactive[obj->nTracks-1])) {

                    obj->idsRemoved[iTrackMax] = obj->ids[iTrackMax];

                }

                iTrack++;

            }

        }

        // Update IDs

        for (iTrackMax = 0; iTrackMax < obj->nTracksMax; iTrackMax++) {

            if (obj->idsAdded[iTrackMax] != 0) {

                obj->ids[iTrackMax] = obj->idsAdded[iTrackMax];

            }

            if (obj->idsRemoved[iTrackMax] != 0) {

                obj->ids[iTrackMax] = 0;

            }

        }

        // Count

        obj->nTracks = 0;

        for (iTrackMax = 0; iTrackMax < obj->nTracksMax; iTrackMax++) {

            if (obj->ids[iTrackMax] != 0) {

                obj->nTracks++;

            }

        }


        // Copy in tracking
   
        memset(msg_tracks->tracks->array, 0x00, sizeof(float) * msg_tracks->tracks->nTracks * 3);
        iTrack = 0;

        for (iTrackMax = 0; iTrackMax < obj->nTracksMax; iTrackMax++) {

            if (obj->ids[iTrackMax] != 0) {

                if (obj->type[iTrackMax] == 'A') {

                    if (strcmp(obj->mode,"kalman") == 0) {

                        kalman2kalman_estimate(obj->kalman2kalman_active, 
                                               obj->kalmans[iTrackMax], 
                                               &x, 
                                               &y, 
                                               &z);

                    }
                    else {

                        particle2particle_estimate(obj->particle2particle_active, 
                                                   obj->particles[iTrackMax], 
                                                   &x,
                                                   &y,
                                                   &z);

                    }

                    msg_tracks->tracks->array[iTrack * 3 + 0] = x;
                    msg_tracks->tracks->array[iTrack * 3 + 1] = y;
                    msg_tracks->tracks->array[iTrack * 3 + 2] = z;
                    msg_tracks->tracks->ids[iTrack] = obj->ids[iTrackMax];

                    iTrack++;

                }

            }

        }

        //printf("\n\n");

    }

    mod_sst_cfg * mod_sst_cfg_construct(void) {

        mod_sst_cfg * cfg;

        cfg = (mod_sst_cfg *) malloc(sizeof(mod_sst_cfg));

        cfg->nPots = 0;
        cfg->nTracks = 0;

        cfg->mode = (char *) NULL;

        cfg->R = 0;
        cfg->hopSize = 0;
        cfg->fS = 0;
        cfg->sigmaQ = 0.0f;
        
        cfg->nParticles = 0;
        cfg->st_alpha = 0.0f;
        cfg->st_beta = 0.0f;
        cfg->st_ratio = 0.0f;
        cfg->ve_alpha = 0.0f;
        cfg->ve_beta = 0.0f;
        cfg->ve_ratio = 0.0f;
        cfg->ac_alpha = 0.0f;
        cfg->ac_beta = 0.0f;
        cfg->ac_ratio = 0.0f;
        cfg->Nmin = 0.0f;

        cfg->epsilon = 0.0f;
        cfg->sigmaR_prob = 0.0f;
        cfg->sigmaR_active = 0.0f;
        cfg->active_gmm = (gaussians_1d_obj *) NULL;
        cfg->inactive_gmm = (gaussians_1d_obj *) NULL;
        cfg->Pfalse = 0.0f;
        cfg->Pnew = 0.0f;
        cfg->Ptrack = 0.0f;
        cfg->shape = (char *) NULL;

        cfg->theta_new = 0.0f;
        cfg->N_prob = 0;
        cfg->theta_prob = 0.0f;
        cfg->N_inactive = (unsigned int *) NULL;
        cfg->theta_inactive = 0.0f;

        return cfg;

    }

    void mod_sst_cfg_destroy(mod_sst_cfg * cfg) {

        if (cfg->mode != NULL) {
            free((void *) cfg->mode);
        }

        if (cfg->active_gmm != NULL) {
            gaussians_1d_destroy(cfg->active_gmm);
        }

        if (cfg->inactive_gmm != NULL) {
            gaussians_1d_destroy(cfg->inactive_gmm);
        }

        if (cfg->shape != NULL) {
            free((void *) cfg->shape);
        }

        if (cfg->N_inactive != NULL) {
            free((void *) cfg->N_inactive);
        }

        free((void *) cfg);

    }