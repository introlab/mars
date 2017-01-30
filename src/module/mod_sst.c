    
    #include "mod_sst.h"

    mod_sst_obj * mod_sst_construct(const mod_sst_cfg * cfg) {

        mod_sst_obj * obj;
        unsigned int iT;
        float deltaT;
        float diffuse_cst;

        obj = (mod_sst_obj *) malloc(sizeof(mod_sst_obj));

        obj->S = cfg->nPots;
        obj->Tmax = cfg->nTracks;
        obj->T = 0;

        obj->mode = (char *) malloc(sizeof(char) * (strlen(cfg->mode) + 1));
        strcpy(obj->mode, cfg->mode);

        obj->mixtures = (mixture_obj **) malloc(sizeof(mixture_obj *) * (obj->Tmax+1));
        obj->coherences = (coherences_obj **) malloc(sizeof(coherences_obj *) * (obj->Tmax+1));
        obj->postprobs = (postprobs_obj **) malloc(sizeof(postprobs_obj *) * (obj->Tmax+1));

        for (iT = 0; iT <= obj->Tmax; iT++) {

        	obj->mixtures[iT] = mixture_construct_zero(obj->S, iT);
        	obj->coherences[iT] = coherences_construct_zero(obj->S, iT);
            obj->postprobs[iT] = postprobs_construct_zero(obj->S, iT); 

        }

        obj->ids = (unsigned long long *) malloc(sizeof(unsigned long long) * obj->Tmax);
        obj->idsAdded = (unsigned long long *) malloc(sizeof(unsigned long long) * obj->Tmax);
        obj->idsRemoved = (unsigned long long *) malloc(sizeof(unsigned long long) * obj->Tmax);
                
        obj->type = (char *) malloc(sizeof(char) * obj->Tmax);

        if (strcmp(obj->mode, "kalman") == 0) {
        
            obj->kalmans = (kalman_obj **) malloc(sizeof(kalman_obj *) * obj->Tmax);    

        }
        else {

            obj->particles = (particles_obj **) malloc(sizeof(particles_obj *) * obj->Tmax);

        }

        
        obj->theta_new = cfg->theta_new;
        obj->N_prob = cfg->N_prob;
        obj->theta_prob = cfg->theta_prob;
        obj->N_inactive = (unsigned int *) malloc(sizeof(unsigned int) * obj->Tmax);
        
        for (iT = 0; iT < obj->Tmax; iT++) {
            obj->N_inactive[iT] = cfg->N_inactive[iT];
        }

        obj->theta_inactive = cfg->theta_inactive;

        obj->n_prob = (unsigned int *) malloc(sizeof(unsigned int) * obj->Tmax);
        obj->mean_prob = (float *) malloc(sizeof(float) * obj->Tmax);
        obj->n_inactive = (unsigned int *) malloc(sizeof(unsigned int) * obj->Tmax);

        for (iT = 0; iT < obj->Tmax; iT++) {

            obj->ids[iT] = 0;
            obj->idsAdded[iT] = 0;
            obj->idsRemoved[iT] = 0;

            obj->type[iT] = 'I';

            if (strcmp(obj->mode, "kalman") == 0) {
                obj->kalmans[iT] =  kalman_construct_zero();    
            }
            else {
                obj->particles[iT] =  particles_construct_zero(cfg->nParticles);       
            }
            
            obj->n_prob[iT] = 0;
            obj->mean_prob[iT] = 0.0f;
            obj->n_inactive[iT] = 0;

        }       

        if (strcmp(cfg->shape,"halfsphere") == 0) {
            diffuse_cst = 1.0f / (2*M_PI);
        }
        else {
            diffuse_cst = 1.0f / (4*M_PI);
        }

        deltaT = ((float) (cfg->R * cfg->hopSize)) / ((float) cfg->fS);
        
        if (strcmp(obj->mode, "kalman") == 0) {

            obj->kalman2kalman = kalman2kalman_construct(deltaT,
                                                         cfg->sigmaQ,
                                                         cfg->sigmaR,
                                                         cfg->epsilon);    

            obj->kalman2coherence = kalman2coherence_construct(cfg->epsilon, 
                                                               cfg->sigmaR);

        }
        else {

            obj->particle2particle = particle2particle_construct(cfg->nParticles,
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
                                                                 cfg->sigmaR,
                                                                 cfg->Nmin);

            obj->particle2coherence = particle2coherence_construct(cfg->sigmaR);

        }


        obj->mixture2mixture = mixture2mixture_construct(cfg->active_gmm,
                                                         cfg->inactive_gmm,
                                                         diffuse_cst,
                                                         cfg->Pfalse,
                                                         cfg->Pnew,
                                                         cfg->Ptrack);

        obj->coord = coord_construct_zero();

        obj->id = 0;

        return obj;

    }

    void mod_sst_destroy(mod_sst_obj * obj) {

    }

    void mod_sst_process(mod_sst_obj * obj, const msg_pots_obj * msg_pots, msg_tracks_obj * msg_tracks) {

        unsigned int iS;
        unsigned int iT;
        unsigned int iTrack;
        float x,y,z;

        // Count

        obj->T = 0;

        for (iT = 0; iT < obj->Tmax; iT++) {

            if (obj->ids[iT] != 0) {

                obj->T++;

            }

        }

        // Predict  

        for (iT = 0; iT < obj->Tmax; iT++) {

            if (obj->ids[iT] != 0) {

                if (strcmp(obj->mode,"kalman") == 0) {

                    kalman2kalman_predict(obj->kalman2kalman,
                                          obj->kalmans[iT]);                

                }
                else {

                    particle2particle_predict(obj->particle2particle,
                                              obj->particles[iT]);                        

                }


            }

        }

        // Coherence

        iTrack = 0;

        for (iT = 0; iT < obj->Tmax; iT++) {

            if (obj->ids[iT] != 0) {

                if (strcmp(obj->mode,"kalman") == 0) {

                    kalman2coherence_process(obj->kalman2coherence,
                                             obj->kalmans[iT],
                                             msg_pots->pots,
                                             obj->coherences[obj->T]->array[iTrack]);

                }
                else {

                    particle2coherence_process(obj->particle2coherence,
                                               obj->particles[iT],
                                               msg_pots->pots,
                                               obj->coherences[obj->T]->array[iTrack]);

                }

                iTrack++;

            }

        }

        // Mixture

        mixture2mixture_process(obj->mixture2mixture, 
        	                    obj->mixtures[obj->T], 
        	                    msg_pots->pots, 
        	                    obj->coherences[obj->T], 
        	                    obj->postprobs[obj->T]);
        
        // Update

        iTrack = 0;

        for (iT = 0; iT < obj->Tmax; iT++) {

            if (obj->ids[iT] != 0) {

                if (strcmp(obj->mode,"kalman") == 0) {

                    kalman2kalman_update(obj->kalman2kalman,
                                         obj->postprobs[obj->T]->p_track[iTrack],
                                         msg_pots->pots,
                                         obj->kalmans[iT]);
                }
                else {

                    particle2particle_update(obj->particle2particle,
                                             obj->postprobs[obj->T]->p_track[iTrack],
                                             msg_pots->pots,
                                             obj->particles[iT]);

                }

                iTrack++;

            }

        }

        // Activity

        iTrack = 0;

        for (iT = 0; iT < obj->Tmax; iT++) {

            if (obj->ids[iT] != 0) {

                // Update counters
                
                switch (obj->type[iT]) {
                    
                    case 'P':

                        obj->n_prob[iT]++;
                        obj->mean_prob[iT] += obj->postprobs[obj->T]->p_track[iTrack]->probTotal;

                    break;

                    case 'A':

                        if (obj->postprobs[obj->T]->p_track[iTrack]->probTotal >= obj->theta_inactive) {
                            obj->n_inactive[iT] = 0;
                        }
                        else {
                            obj->n_inactive[iT]++;   
                        }

                    break;

                }

                iTrack++;

            }

        }        

        // Transitions

        iTrack = 0;

        for (iT = 0; iT < obj->Tmax; iT++) {

            if (obj->ids[iT] != 0) {

                if ((obj->type[iT] == 'P') && 
                    (obj->n_prob[iT] == obj->N_prob) && 
                    (obj->mean_prob[iT]/((float) obj->N_prob) >= obj->theta_prob)) {

                    obj->type[iT] = 'A';
                    obj->n_inactive[iT] = 0;

                }

                iTrack++;

            }

        }          

        // Add source
        
        for (iT = 0; iT < obj->Tmax; iT++) {

            obj->idsAdded[iT] = 0;

        }

        for (iS = 0; iS < obj->S; iS++) {

            if (obj->postprobs[obj->T]->p_new->probs[iS] > obj->theta_new) {                

                for (iT = 0; iT < obj->Tmax; iT++) {

                    if (obj->ids[iT] == 0) {

                        obj->id++;
                        obj->idsAdded[iT] = obj->id;
                        
                        if (strcmp(obj->mode,"kalman") == 0) {

                            kalman2kalman_init(obj->kalman2kalman, msg_pots->pots->array[iS], obj->kalmans[iT]); 

                        }
                        else {

                            particle2particle_init(obj->particle2particle, msg_pots->pots->array[iS], obj->particles[iT]);

                        }
                        
                        obj->type[iT] = 'P';
                        obj->n_prob[iT] = 0;
                        obj->mean_prob[iT] = 0.0f;

                        break;

                    }

                }

            }

        }

        // Remove source

        for (iT = 0; iT < obj->Tmax; iT++) {

            obj->idsRemoved[iT] = 0;
            
        }

        iTrack = 0;

        for (iT = 0; iT < obj->Tmax; iT++) {

            if (obj->ids[iT] != 0) {

                if ((obj->type[iT] == 'P') && 
                    (obj->n_prob[iT] == obj->N_prob) && 
                    (obj->mean_prob[iT]/((float) obj->N_prob) < obj->theta_prob)) {

                    obj->idsRemoved[iT] = obj->ids[iT];

                }

                if ((obj->type[iT] == 'A') &&
                    (obj->n_inactive[iT] >= obj->N_inactive[obj->T-1])) {

                    obj->idsRemoved[iT] = obj->ids[iT];

                }

                iTrack++;

            }

        }

        // Update IDs

        for (iT = 0; iT < obj->Tmax; iT++) {

            if (obj->idsAdded[iT] != 0) {

                obj->ids[iT] = obj->idsAdded[iT];

            }

            if (obj->idsRemoved[iT] != 0) {

                obj->ids[iT] = 0;

            }

        }

        // Count

        obj->T = 0;

        for (iT = 0; iT < obj->Tmax; iT++) {

            if (obj->ids[iT] != 0) {

                obj->T++;

            }

        }


        // Copy in tracking
   
        tracks_copy_zero(msg_tracks->tracks);
        iTrack = 0;

        for (iT = 0; iT < obj->Tmax; iT++) {

            if (obj->ids[iT] != 0) {

                if (obj->type[iT] == 'A') {

                    if (strcmp(obj->mode,"kalman") == 0) {

                        kalman2kalman_estimate(obj->kalman2kalman, obj->kalmans[iT], obj->coord);

                    }
                    else {

                        particle2particle_estimate(obj->particle2particle, obj->particles[iT], obj->coord);

                    }

                    track_copy_idxyz(msg_tracks->tracks->array[iTrack], obj->ids[iT], obj->coord->x, obj->coord->y, obj->coord->z);                    

                    iTrack++;

                }

            }

        }


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
        cfg->sigmaR = 0.0f;
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
            free((void *) cfg->mode);
        }

        free((void *) cfg);

    }