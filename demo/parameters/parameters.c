
    #include "parameters.h"

    parameters_obj * parameters_construct_file(const char * fileName) {

        parameters_obj * obj;

        config_t cfg;
        config_setting_t * setting;
        int i;
        int N;
        int valueInt;
        double valueDouble;
        char * valueString;

        obj = (parameters_obj *) malloc(sizeof(parameters_obj));

        obj->general = (parameters_general_obj *) malloc(sizeof(parameters_general_obj));
        obj->raw = (parameters_raw_obj *) malloc(sizeof(parameters_raw_obj));
        obj->ssl = (parameters_ssl_obj *) malloc(sizeof(parameters_ssl_obj));
        obj->sst = (parameters_sst_obj *) malloc(sizeof(parameters_sst_obj));

        config_init(&cfg);        

        /* Read the file. If there is an error, report it and exit. */
        if(!config_read_file(&cfg, fileName))
        {
            
            printf("%s:%d - %s\n", config_error_file(&cfg), config_error_line(&cfg), config_error_text(&cfg));
            config_destroy(&cfg);
          
            exit(EXIT_FAILURE);

        }     

        // General

            // hopSize
            if (config_lookup_int(&cfg, "general.hopSize", &valueInt)) { 
                obj->general->hopSize = valueInt;
            }
            else {
                printf("Missing: general.hopSize\n"); 
                exit(EXIT_FAILURE);
            }

            // frameSize
            if (config_lookup_int(&cfg, "general.frameSize", &valueInt)) { 
                obj->general->frameSize = valueInt; 
            } 
            else {
                printf("Missing: general.frameSize\n"); 
                exit(EXIT_FAILURE); 
            }

            // fS
            if (config_lookup_int(&cfg, "general.fS", &valueInt)) {
                obj->general->fS = valueInt;
            } 
            else { 
                printf("Missing: general.fS\n"); 
                exit(EXIT_FAILURE); 
            }

            // c
            if (config_lookup_float(&cfg, "general.c", &valueDouble)) { 
                obj->general->c = (float) valueDouble; 
            } 
            else { 
                printf("Missing: general.c\n"); 
                exit(EXIT_FAILURE); 
            }

            // mics
            setting = config_lookup(&cfg, "general.mics");

            if (setting != NULL) {

                N = config_setting_length(setting);

                obj->general->mics = mics_construct_zero(N);

                for (i = 0; i < N; i++) {

                    config_setting_lookup_float(config_setting_get_elem(setting, i),"x",&valueDouble);
                    obj->general->mics->array[i]->coord->x = (float) valueDouble;
                    config_setting_lookup_float(config_setting_get_elem(setting, i),"y",&valueDouble);
                    obj->general->mics->array[i]->coord->y = (float) valueDouble;
                    config_setting_lookup_float(config_setting_get_elem(setting, i),"z",&valueDouble);
                    obj->general->mics->array[i]->coord->z = (float) valueDouble;

                }

            }
            else {
                
                printf("Missing: general.mics\n"); exit(EXIT_FAILURE);

            }

        // Raw

            // nBits
            if (config_lookup_int(&cfg, "raw.nBits", &valueInt)) { 
                obj->raw->nBits = valueInt;
            } 
            else { 
                printf("Missing: raw.nBits\n"); 
                exit(EXIT_FAILURE);
            }

        // SSL

            // R
            if (config_lookup_int(&cfg, "ssl.R", &valueInt)) { 
                obj->ssl->R = (unsigned int) valueInt;
            }
            else { 
                printf("Missing: ssl.R\n");
                exit(EXIT_FAILURE);
            }    
    
            // alpha    
            if (config_lookup_float(&cfg, "ssl.alpha", &valueDouble)) { 
                obj->ssl->alpha = (float) valueDouble; 
            } 
            else { 
                printf("Missing: ssl.alpha\n"); 
                exit(EXIT_FAILURE); 
            }    

            // sigma
            if (config_lookup_float(&cfg, "ssl.sigma", &valueDouble)) { 
                obj->ssl->sigma = (float) valueDouble; 
            } 
            else { 
                printf("Missing: ssl.sigma\n"); 
                exit(EXIT_FAILURE); 
            }    

            // nMatches
            if (config_lookup_int(&cfg, "ssl.nMatches", &valueInt)) { 
                obj->ssl->nMatches = (unsigned int) valueInt;
            } 
            else { 
                printf("Missing: ssl.nMatches\n"); 
                exit(EXIT_FAILURE); 
            }    

            // epsilon
            if (config_lookup_float(&cfg, "ssl.epsilon", &valueDouble)) { 
                obj->ssl->epsilon = (float) valueDouble;
            } 
            else { 
                printf("Missing: ssl.epsilon\n"); 
                exit(EXIT_FAILURE);
            }    

            // deltaReset
            if (config_lookup_int(&cfg, "ssl.deltaReset", &valueInt)) { 
                obj->ssl->deltaReset = (unsigned int) valueInt;
            } 
            else { 
                printf("Missing: ssl.nMatches\n"); 
                exit(EXIT_FAILURE); 
            }    
        
            // nPots
            if (config_lookup_int(&cfg, "ssl.nPots", &valueInt)) { 
                obj->ssl->nPots = (unsigned int) valueInt;
            } 
            else {
                printf("Missing: ssl.nPots\n"); 
                exit(EXIT_FAILURE); 
            }    

            // scans
            setting = config_lookup(&cfg, "ssl.scans");

            if (setting != NULL) {

                N = config_setting_length(setting);

                obj->ssl->nLevels = N;
                obj->ssl->levels = (unsigned int *) malloc(sizeof(unsigned int) * N);
                obj->ssl->deltasMax = (unsigned int *) malloc(sizeof(unsigned int) * N);

                for (i = 0; i < N; i++) {

                    config_setting_lookup_int(config_setting_get_elem(setting, i),"level",&valueInt);
                    obj->ssl->levels[i] = valueInt;
                    config_setting_lookup_int(config_setting_get_elem(setting, i),"deltaMax",&valueInt);
                    obj->ssl->deltasMax[i] = valueInt;

                }

            }
            else {
                
                printf("Missing: ssl.levels\n"); exit(EXIT_FAILURE);

            }

            // shape
            if (config_lookup_string(&cfg, "ssl.shape", (const char **) &valueString)) { 

            } 
            else { 
                printf("Missing: ssl.shape\n"); 
                exit(EXIT_FAILURE); 
            }    

            obj->ssl->shape = (char *) malloc(sizeof(char) * (strlen(valueString)+1));
            strcpy(obj->ssl->shape, valueString);

        // SST

            // mode
            if (config_lookup_string(&cfg, "sst.mode", (const char **) &valueString)) {

            }
            else { 
                printf("Missing: sst.mode\n"); 
                exit(EXIT_FAILURE); 
            }    

            obj->sst->mode = (char *) malloc(sizeof(char) * (strlen(valueString)+1));
            strcpy(obj->sst->mode, valueString);
        
            // epsilon
            if (config_lookup_float(&cfg, "sst.epsilon", &valueDouble)) { 
                obj->sst->epsilon = (float) valueDouble;
            } 
            else { 
                printf("Missing: sst.epsilon\n"); 
                exit(EXIT_FAILURE); 
            }    

            // sigmaR
            if (config_lookup_float(&cfg, "sst.sigmaR", &valueDouble)) { 
                obj->sst->sigmaR = (float) valueDouble;
            } 
            else { 
                printf("Missing: sst.sigmaR\n"); 
                exit(EXIT_FAILURE); 
            }    

            // active
            setting = config_lookup(&cfg, "sst.active"); 

            if (setting != NULL) {

                N = config_setting_length(setting);

                obj->sst->active_G = N;
                obj->sst->active_weight = (float *) malloc(sizeof(float) * N);
                obj->sst->active_mu = (float *) malloc(sizeof(float) * N);
                obj->sst->active_sigma = (float *) malloc(sizeof(float) * N);

                for (i = 0; i < N; i++) {

                    config_setting_lookup_float(config_setting_get_elem(setting, i),"weight",&valueDouble);
                    obj->sst->active_weight[i] = (float) valueDouble;
                    config_setting_lookup_float(config_setting_get_elem(setting, i),"mu",&valueDouble);
                    obj->sst->active_mu[i] = (float) valueDouble;
                    config_setting_lookup_float(config_setting_get_elem(setting, i),"sigma",&valueDouble);
                    obj->sst->active_sigma[i] = (float) valueDouble;

                }

            }
            else {
                
                printf("Missing: sst.active\n"); 
                exit(EXIT_FAILURE);

            }        

            // inactive
            setting = config_lookup(&cfg, "sst.inactive"); 

            if (setting != NULL) {

                N = config_setting_length(setting);

                obj->sst->inactive_G = N;
                obj->sst->inactive_weight = (float *) malloc(sizeof(float) * N);
                obj->sst->inactive_mu = (float *) malloc(sizeof(float) * N);
                obj->sst->inactive_sigma = (float *) malloc(sizeof(float) * N);

                for (i = 0; i < N; i++) {

                    config_setting_lookup_float(config_setting_get_elem(setting, i),"weight",&valueDouble);
                    obj->sst->inactive_weight[i] = (float) valueDouble;
                    config_setting_lookup_float(config_setting_get_elem(setting, i),"mu",&valueDouble);
                    obj->sst->inactive_mu[i] = (float) valueDouble;
                    config_setting_lookup_float(config_setting_get_elem(setting, i),"sigma",&valueDouble);
                    obj->sst->inactive_sigma[i] = (float) valueDouble;

                }

            }
            else {
                
                printf("Missing: sst.inactive\n"); exit(EXIT_FAILURE);

            }   

            // Pfalse
            if (config_lookup_float(&cfg, "sst.Pfalse", &valueDouble)) { 
                obj->sst->Pfalse = (float) valueDouble; 
            } 
            else { 
                printf("Missing: sst.Pfalse\n"); 
                exit(EXIT_FAILURE); 
            }    

            // Pnew
            if (config_lookup_float(&cfg, "sst.Pnew", &valueDouble)) { 
                obj->sst->Pnew = (float) valueDouble; 
            } 
            else { 
                printf("Missing: sst.Pnew\n"); 
                exit(EXIT_FAILURE); 
            }    

            // Ptrack
            if (config_lookup_float(&cfg, "sst.Ptrack", &valueDouble)) { 
                obj->sst->Ptrack = (float) valueDouble; 
            } 
            else { 
                printf("Missing: sst.Ptrack\n"); 
                exit(EXIT_FAILURE); 
            }

            // Theta
            if (config_lookup_float(&cfg, "sst.theta_new", &valueDouble)) { 
                obj->sst->theta_new = (float) valueDouble; 
            } 
            else { 
                printf("Missing: sst.theta_new\n"); 
                exit(EXIT_FAILURE); 
            }    

            // N_prob
            if (config_lookup_int(&cfg, "sst.N_prob", &valueInt)) { 
                obj->sst->N_prob = (unsigned int) valueInt; 
            } 
            else { 
                printf("Missing: sst.N_prob\n"); 
                exit(EXIT_FAILURE); 
            }    

            // theta_prob
            if (config_lookup_float(&cfg, "sst.theta_prob", &valueDouble)) { 
                obj->sst->theta_prob = (float) valueDouble; 
            } 
            else { 
                printf("Missing: sst.theta_prob\n"); 
                exit(EXIT_FAILURE); 
            }    
        
            // N_inactive
            setting = config_lookup(&cfg, "sst.N_inactive"); 

            if (setting != NULL) {

                N = config_setting_length(setting);

                obj->sst->nTracks = N;

                obj->sst->N_inactive = (unsigned int *) malloc(sizeof(unsigned int) * N);

                for (i = 0; i < N; i++) {

                    obj->sst->N_inactive[i] = (unsigned int) config_setting_get_int_elem(setting, i);

                }

            }
            else {

                printf("Missing: sst.N_inactive\n"); exit(EXIT_FAILURE);

            }

            // theta_inactive
            if (config_lookup_float(&cfg, "sst.theta_inactive", &valueDouble)) { 
                obj->sst->theta_inactive = (float) valueDouble; 
            } 
            else { 
                printf("Missing: sst.theta_inactive\n"); 
                exit(EXIT_FAILURE);
            }    

            // Kalman filter
        
                // sigmaQ
                if (config_lookup_float(&cfg, "sst.kalman.sigmaQ", &valueDouble)) { 
                    obj->sst->sigmaQ = (float) valueDouble; 
                } 
                else { 
                    printf("Missing: sst.kalman.sigmaQ\n"); 
                    exit(EXIT_FAILURE); 
                }    

            // Particle filter

                // nParticles
                if (config_lookup_int(&cfg, "sst.particle.nParticles", &valueInt)) { 
                    obj->sst->nParticles = (unsigned int) valueInt; 
                } 
                else { 
                    printf("Missing: sst.particle.nParticles\n"); 
                    exit(EXIT_FAILURE); 
                }    

                // st_alpha
                if (config_lookup_float(&cfg, "sst.particle.st_alpha", &valueDouble)) { 
                    obj->sst->st_alpha = (float) valueDouble; 
                } 
                else { 
                    printf("Missing: sst.particle.st_alpha\n"); 
                    exit(EXIT_FAILURE); 
                }    

                // st_beta
                if (config_lookup_float(&cfg, "sst.particle.st_beta", &valueDouble)) { 
                    obj->sst->st_beta = (float) valueDouble;
                } 
                else { 
                    printf("Missing: sst.particle.st_beta\n"); 
                    exit(EXIT_FAILURE); 
                }    
        
                // st_ratio
                if (config_lookup_float(&cfg, "sst.particle.st_ratio", &valueDouble)) { 
                    obj->sst->st_ratio = (float) valueDouble; 
                } 
                else { 
                    printf("Missing: sst.particle.st_ratio\n"); 
                    exit(EXIT_FAILURE); 
                }    
        
                // ve_alpha
                if (config_lookup_float(&cfg, "sst.particle.ve_alpha", &valueDouble)) { 
                    obj->sst->ve_alpha = (float) valueDouble; 
                } 
                else { 
                    printf("Missing: sst.particle.ve_alpha\n"); 
                    exit(EXIT_FAILURE); 
                }    
        
                // ve_beta
                if (config_lookup_float(&cfg, "sst.particle.ve_beta", &valueDouble)) { 
                    obj->sst->ve_beta = (float) valueDouble; 
                } 
                else { 
                    printf("Missing: sst.particle.ve_beta\n"); 
                    exit(EXIT_FAILURE); 
                }    

                // ve_ratio
                if (config_lookup_float(&cfg, "sst.particle.ve_ratio", &valueDouble)) { 
                    obj->sst->ve_ratio = (float) valueDouble; 
                } 
                else { 
                    printf("Missing: sst.particle.ve_ratio\n"); 
                    exit(EXIT_FAILURE); 
                }    

                // ac_alpha
                if (config_lookup_float(&cfg, "sst.particle.ac_alpha", &valueDouble)) { 
                    obj->sst->ac_alpha = (float) valueDouble; 
                } 
                else { 
                    printf("Missing: sst.particle.ac_alpha\n"); 
                    exit(EXIT_FAILURE); 
                }    

                // ac_beta
                if (config_lookup_float(&cfg, "sst.particle.ac_beta", &valueDouble)) { 
                    obj->sst->ac_beta = (float) valueDouble;
                } 
                else { 
                    printf("Missing: sst.particle.ac_beta\n"); 
                    exit(EXIT_FAILURE); 
                }    

                // ac_ratio
                if (config_lookup_float(&cfg, "sst.particle.ac_ratio", &valueDouble)) { 
                    obj->sst->ac_ratio = (float) valueDouble; 
                } 
                else { 
                    printf("Missing: sst.particle.ac_ratio\n"); 
                    exit(EXIT_FAILURE); 
                }    
        
                // Nmin
                if (config_lookup_float(&cfg, "sst.particle.Nmin", &valueDouble)) { 
                    obj->sst->Nmin = (float) valueDouble; 
                } 
                else { 
                    printf("Missing: sst.particle.Nmin\n"); 
                    exit(EXIT_FAILURE); 
                }    

        config_destroy(&cfg);        

        return obj;

    }

    void parameters_destroy(parameters_obj * obj) {

    }