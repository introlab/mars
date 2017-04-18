
    #include "file2parameters.h"

    void file2parameters(parameters * params, const char * fileName) {

        config_t cfg;
        config_setting_t * setting;
        int i;
        int N;
        int valueInt;
        double valueDouble;
        char * valueString;

        params->general = (parameters_general_obj *) malloc(sizeof(parameters_general_obj));
        params->raw = (parameters_raw_obj *) malloc(sizeof(parameters_raw_obj));
        params->ssl = (parameters_ssl_obj *) malloc(sizeof(parameters_ssl_obj));
        params->sst = (parameters_sst_obj *) malloc(sizeof(parameters_sst_obj));        

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
                params->general->hopSize = valueInt;
            }
            else {
                printf("Missing: general.hopSize\n"); 
                exit(EXIT_FAILURE);
            }

            // frameSize
            if (config_lookup_int(&cfg, "general.frameSize", &valueInt)) { 
                params->general->frameSize = valueInt; 
            } 
            else {
                printf("Missing: general.frameSize\n"); 
                exit(EXIT_FAILURE); 
            }

            // fS
            if (config_lookup_int(&cfg, "general.fS", &valueInt)) {
                params->general->fS = valueInt;
            } 
            else { 
                printf("Missing: general.fS\n"); 
                exit(EXIT_FAILURE); 
            }

            // speed of sound

            params->general->soundspeed = soundspeed_construct_zero();

            if (config_lookup_float(&cfg, "general.c.mu", &valueDouble)) { 
                params->general->soundspeed->mu = (float) valueDouble; 
            } 
            else { 
                printf("Missing: general.c.mu\n"); 
                exit(EXIT_FAILURE); 
            }
            if (config_lookup_float(&cfg, "general.c.sigma", &valueDouble)) { 
                params->general->soundspeed->sigma = (float) valueDouble; 
            } 
            else { 
                printf("Missing: general.c.sigma\n"); 
                exit(EXIT_FAILURE); 
            }

            // mics
            setting = config_lookup(&cfg, "general.mics");

            if (setting != NULL) {

                N = config_setting_length(setting);

                params->general->mics = mics_construct_zero(N);

                for (i = 0; i < N; i++) {

                    if (config_setting_lookup_float(config_setting_get_elem(setting, i),"x",&valueDouble)) {
                        params->general->mics->mu[i * 3 + 0] = (float) valueDouble;    
                    }
                    else {
                        printf("Missing: general.mics[%u].x\n",i); 
                        exit(EXIT_FAILURE);                         
                    }
                    
                    if (config_setting_lookup_float(config_setting_get_elem(setting, i),"y",&valueDouble)) {
                        params->general->mics->mu[i * 3 + 1] = (float) valueDouble;    
                    }
                    else {
                        printf("Missing: general.mics[%u].y\n",i); 
                        exit(EXIT_FAILURE);                         
                    }                    
                    
                    if (config_setting_lookup_float(config_setting_get_elem(setting, i),"z",&valueDouble)) {
                        params->general->mics->mu[i * 3 + 2] = (float) valueDouble;    
                    }
                    else {
                        printf("Missing: general.mics[%u].z\n",i); 
                        exit(EXIT_FAILURE);                         
                    }                    
                    
                    if (config_setting_lookup_float(config_setting_get_elem(setting, i),"xx",&valueDouble)) {
                        params->general->mics->sigma[i * 9 + 0] = (float) valueDouble;    
                    }
                    else {
                        printf("Missing: general.mics[%u].xx\n",i); 
                        exit(EXIT_FAILURE);                         
                    }                                       
                    
                    if (config_setting_lookup_float(config_setting_get_elem(setting, i),"xy",&valueDouble)) {
                        params->general->mics->sigma[i * 9 + 1] = (float) valueDouble;    
                    }
                    else {
                        printf("Missing: general.mics[%u].xy\n",i); 
                        exit(EXIT_FAILURE);                         
                    }                                                          
                    
                    if (config_setting_lookup_float(config_setting_get_elem(setting, i),"xz",&valueDouble)) {
                        params->general->mics->sigma[i * 9 + 2] = (float) valueDouble;                        
                    }
                    else {
                        printf("Missing: general.mics[%u].xz\n",i); 
                        exit(EXIT_FAILURE);                         
                    }                                                                             
                    
                    if (config_setting_lookup_float(config_setting_get_elem(setting, i),"yx",&valueDouble)) {
                        params->general->mics->sigma[i * 9 + 3] = (float) valueDouble;    
                    }
                    else {
                        printf("Missing: general.mics[%u].yx\n",i); 
                        exit(EXIT_FAILURE);                         
                    }                                                                                                
                    
                    if (config_setting_lookup_float(config_setting_get_elem(setting, i),"yy",&valueDouble)) {
                        params->general->mics->sigma[i * 9 + 4] = (float) valueDouble;
                    }
                    else {
                        printf("Missing: general.mics[%u].yy\n",i); 
                        exit(EXIT_FAILURE);                         
                    }                                                                                                

                    if (config_setting_lookup_float(config_setting_get_elem(setting, i),"yz",&valueDouble)) {
                        params->general->mics->sigma[i * 9 + 5] = (float) valueDouble;
                    }
                    else {
                        printf("Missing: general.mics[%u].yz\n",i); 
                        exit(EXIT_FAILURE);                         
                    }                                                                                                                   
                    
                    if (config_setting_lookup_float(config_setting_get_elem(setting, i),"zx",&valueDouble)) {
                        params->general->mics->sigma[i * 9 + 6] = (float) valueDouble;    
                    }
                    else {
                        printf("Missing: general.mics[%u].zx\n",i); 
                        exit(EXIT_FAILURE);                         
                    }                                                                                                                                       
                    
                    if (config_setting_lookup_float(config_setting_get_elem(setting, i),"zy",&valueDouble)) {
                        params->general->mics->sigma[i * 9 + 7] = (float) valueDouble;    
                    }
                    else {
                        printf("Missing: general.mics[%u].zy\n",i); 
                        exit(EXIT_FAILURE);                         
                    }                                                                                                                                       
                    
                    if (config_setting_lookup_float(config_setting_get_elem(setting, i),"zz",&valueDouble)) {
                        params->general->mics->sigma[i * 9 + 8] = (float) valueDouble;
                    }
                    else {
                        printf("Missing: general.mics[%u].zz\n",i); 
                        exit(EXIT_FAILURE);                         
                    }                                                                                                                                       

                }

            }
            else {
                
                printf("Missing: general.mics\n"); exit(EXIT_FAILURE);

            }

        // Raw

            // nBitsIn
            if (config_lookup_int(&cfg, "raw.in.nBits", &valueInt)) { 
                params->raw->nBitsIn = valueInt;
            } 
            else { 
                printf("Missing: raw.in.nBits\n"); 
                exit(EXIT_FAILURE);
            }

            // hopSizeIn
            if (config_lookup_int(&cfg, "raw.in.hopSize", &valueInt)) { 
                params->raw->hopSizeIn = valueInt;
            } 
            else { 
                printf("Missing: raw.in.hopSize\n"); 
                exit(EXIT_FAILURE);
            }            
            
            // nBitsOut
            if (config_lookup_int(&cfg, "raw.out.nBits", &valueInt)) { 
                params->raw->nBitsOut = valueInt;
            } 
            else { 
                printf("Missing: raw.out.nBits\n"); 
                exit(EXIT_FAILURE);
            }

            // hopSizeOut
            if (config_lookup_int(&cfg, "raw.out.hopSize", &valueInt)) { 
                params->raw->hopSizeOut = valueInt;
            } 
            else { 
                printf("Missing: raw.out.hopSize\n"); 
                exit(EXIT_FAILURE);
            }   

        // SSL

            // R
            if (config_lookup_int(&cfg, "ssl.R", &valueInt)) { 
                params->ssl->R = (unsigned int) valueInt;
            }
            else { 
                printf("Missing: ssl.R\n");
                exit(EXIT_FAILURE);
            }    
    
            // alpha    
            if (config_lookup_float(&cfg, "ssl.alpha", &valueDouble)) { 
                params->ssl->alpha = (float) valueDouble; 
            } 
            else { 
                printf("Missing: ssl.alpha\n"); 
                exit(EXIT_FAILURE); 
            }    

            // ratioMatch
            if (config_lookup_float(&cfg, "ssl.ratioMatch", &valueDouble)) { 
                params->ssl->ratioMatch = (float) valueDouble;
            } 
            else { 
                printf("Missing: ssl.ratioMatch\n"); 
                exit(EXIT_FAILURE); 
            }    

            // probMin
            if (config_lookup_float(&cfg, "ssl.probMin", &valueDouble)) { 
                params->ssl->probMin = (float) valueDouble;
            } 
            else { 
                printf("Missing: ssl.probMin\n"); 
                exit(EXIT_FAILURE); 
            }    

            // nRefinedLevels
            if (config_lookup_int(&cfg, "ssl.nRefinedLevels", &valueInt)) { 
                params->ssl->nRefinedLevels = (unsigned int) valueInt;
            } 
            else { 
                printf("Missing: ssl.probMin\n"); 
                exit(EXIT_FAILURE); 
            }    

            // epsilon
            if (config_lookup_float(&cfg, "ssl.epsilon", &valueDouble)) { 
                params->ssl->epsilon = (float) valueDouble;
            } 
            else { 
                printf("Missing: ssl.epsilon\n"); 
                exit(EXIT_FAILURE);
            }    
        
            // nPots
            if (config_lookup_int(&cfg, "ssl.nPots", &valueInt)) { 
                params->ssl->nPots = (unsigned int) valueInt;
            } 
            else {
                printf("Missing: ssl.nPots\n"); 
                exit(EXIT_FAILURE); 
            }    

            // scans
            setting = config_lookup(&cfg, "ssl.scans");

            if (setting != NULL) {

                N = config_setting_length(setting);

                params->ssl->nLevels = N;
                params->ssl->levels = (unsigned int *) malloc(sizeof(unsigned int) * N);
                params->ssl->deltas = (signed int *) malloc(sizeof(signed int) * N);

                for (i = 0; i < N; i++) {

                    if (config_setting_lookup_int(config_setting_get_elem(setting, i),"level",&valueInt)) {
                        params->ssl->levels[i] = valueInt;
                    }
                    else {
                        printf("Missing: ssl.scans[%u].level\n",i);
                        exit(EXIT_FAILURE);
                    }
                    
                    if (config_setting_lookup_int(config_setting_get_elem(setting, i),"delta",&valueInt)) {
                        params->ssl->deltas[i] = valueInt;    
                    }
                    else {
                        printf("Missing: ssl.scans[%u].delta\n",i);
                        exit(EXIT_FAILURE);
                    }

                }

            }
            else {
                
                printf("Missing: ssl.scans\n"); exit(EXIT_FAILURE);

            }

            // shape
            if (config_lookup_string(&cfg, "ssl.shape", (const char **) &valueString)) { 

            } 
            else { 
                printf("Missing: ssl.shape\n"); 
                exit(EXIT_FAILURE); 
            }    

            params->ssl->shape = (char *) malloc(sizeof(char) * (strlen(valueString)+1));
            strcpy(params->ssl->shape, valueString);

        // SST

            // mode
            if (config_lookup_string(&cfg, "sst.mode", (const char **) &valueString)) {

            }
            else { 
                printf("Missing: sst.mode\n"); 
                exit(EXIT_FAILURE); 
            }    

            params->sst->mode = (char *) malloc(sizeof(char) * (strlen(valueString)+1));
            strcpy(params->sst->mode, valueString);
        
            // epsilon
            if (config_lookup_float(&cfg, "sst.epsilon", &valueDouble)) { 
                params->sst->epsilon = (float) valueDouble;
            } 
            else { 
                printf("Missing: sst.epsilon\n"); 
                exit(EXIT_FAILURE); 
            }    

            // sigmaR_active
            if (config_lookup_float(&cfg, "sst.sigmaR_prob", &valueDouble)) { 
                params->sst->sigmaR_prob = (float) valueDouble;
            } 
            else { 
                printf("Missing: sst.sigmaR_prob\n"); 
                exit(EXIT_FAILURE); 
            }    

            // sigmaR_active
            if (config_lookup_float(&cfg, "sst.sigmaR_active", &valueDouble)) { 
                params->sst->sigmaR_active = (float) valueDouble;
            } 
            else { 
                printf("Missing: sst.sigmaR_active\n"); 
                exit(EXIT_FAILURE); 
            }    

            // active
            setting = config_lookup(&cfg, "sst.active"); 

            if (setting != NULL) {

                N = config_setting_length(setting);

                params->sst->active_G = N;
                params->sst->active_weight = (float *) malloc(sizeof(float) * N);
                params->sst->active_mu = (float *) malloc(sizeof(float) * N);
                params->sst->active_sigma = (float *) malloc(sizeof(float) * N);

                for (i = 0; i < N; i++) {

                    config_setting_lookup_float(config_setting_get_elem(setting, i),"weight",&valueDouble);
                    params->sst->active_weight[i] = (float) valueDouble;
                    config_setting_lookup_float(config_setting_get_elem(setting, i),"mu",&valueDouble);
                    params->sst->active_mu[i] = (float) valueDouble;
                    config_setting_lookup_float(config_setting_get_elem(setting, i),"sigma",&valueDouble);
                    params->sst->active_sigma[i] = (float) valueDouble;

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

                params->sst->inactive_G = N;
                params->sst->inactive_weight = (float *) malloc(sizeof(float) * N);
                params->sst->inactive_mu = (float *) malloc(sizeof(float) * N);
                params->sst->inactive_sigma = (float *) malloc(sizeof(float) * N);

                for (i = 0; i < N; i++) {

                    config_setting_lookup_float(config_setting_get_elem(setting, i),"weight",&valueDouble);
                    params->sst->inactive_weight[i] = (float) valueDouble;
                    config_setting_lookup_float(config_setting_get_elem(setting, i),"mu",&valueDouble);
                    params->sst->inactive_mu[i] = (float) valueDouble;
                    config_setting_lookup_float(config_setting_get_elem(setting, i),"sigma",&valueDouble);
                    params->sst->inactive_sigma[i] = (float) valueDouble;

                }

            }
            else {
                
                printf("Missing: sst.inactive\n"); exit(EXIT_FAILURE);

            }   

            // Pfalse
            if (config_lookup_float(&cfg, "sst.Pfalse", &valueDouble)) { 
                params->sst->Pfalse = (float) valueDouble; 
            } 
            else { 
                printf("Missing: sst.Pfalse\n"); 
                exit(EXIT_FAILURE); 
            }    

            // Pnew
            if (config_lookup_float(&cfg, "sst.Pnew", &valueDouble)) { 
                params->sst->Pnew = (float) valueDouble; 
            } 
            else { 
                printf("Missing: sst.Pnew\n"); 
                exit(EXIT_FAILURE); 
            }    

            // Ptrack
            if (config_lookup_float(&cfg, "sst.Ptrack", &valueDouble)) { 
                params->sst->Ptrack = (float) valueDouble; 
            } 
            else { 
                printf("Missing: sst.Ptrack\n"); 
                exit(EXIT_FAILURE); 
            }

            // Theta
            if (config_lookup_float(&cfg, "sst.theta_new", &valueDouble)) { 
                params->sst->theta_new = (float) valueDouble; 
            } 
            else { 
                printf("Missing: sst.theta_new\n"); 
                exit(EXIT_FAILURE); 
            }    

            // N_prob
            if (config_lookup_int(&cfg, "sst.N_prob", &valueInt)) { 
                params->sst->N_prob = (unsigned int) valueInt; 
            } 
            else { 
                printf("Missing: sst.N_prob\n"); 
                exit(EXIT_FAILURE); 
            }    

            // theta_prob
            if (config_lookup_float(&cfg, "sst.theta_prob", &valueDouble)) { 
                params->sst->theta_prob = (float) valueDouble; 
            } 
            else { 
                printf("Missing: sst.theta_prob\n"); 
                exit(EXIT_FAILURE); 
            }    
        
            // N_inactive
            setting = config_lookup(&cfg, "sst.N_inactive"); 

            if (setting != NULL) {

                N = config_setting_length(setting);

                params->sst->nTracks = N;

                params->sst->N_inactive = (unsigned int *) malloc(sizeof(unsigned int) * N);

                for (i = 0; i < N; i++) {

                    params->sst->N_inactive[i] = (unsigned int) config_setting_get_int_elem(setting, i);

                }

            }
            else {

                printf("Missing: sst.N_inactive\n"); exit(EXIT_FAILURE);

            }

            // theta_inactive
            if (config_lookup_float(&cfg, "sst.theta_inactive", &valueDouble)) { 
                params->sst->theta_inactive = (float) valueDouble; 
            } 
            else { 
                printf("Missing: sst.theta_inactive\n"); 
                exit(EXIT_FAILURE);
            }    

            // Kalman filter
        
                // sigmaQ
                if (config_lookup_float(&cfg, "sst.kalman.sigmaQ", &valueDouble)) { 
                    params->sst->sigmaQ = (float) valueDouble; 
                } 
                else { 
                    printf("Missing: sst.kalman.sigmaQ\n"); 
                    exit(EXIT_FAILURE); 
                }    

            // Particle filter

                // nParticles
                if (config_lookup_int(&cfg, "sst.particle.nParticles", &valueInt)) { 
                    params->sst->nParticles = (unsigned int) valueInt; 
                } 
                else { 
                    printf("Missing: sst.particle.nParticles\n"); 
                    exit(EXIT_FAILURE); 
                }    

                // st_alpha
                if (config_lookup_float(&cfg, "sst.particle.st_alpha", &valueDouble)) { 
                    params->sst->st_alpha = (float) valueDouble; 
                } 
                else { 
                    printf("Missing: sst.particle.st_alpha\n"); 
                    exit(EXIT_FAILURE); 
                }    

                // st_beta
                if (config_lookup_float(&cfg, "sst.particle.st_beta", &valueDouble)) { 
                    params->sst->st_beta = (float) valueDouble;
                } 
                else { 
                    printf("Missing: sst.particle.st_beta\n"); 
                    exit(EXIT_FAILURE); 
                }    
        
                // st_ratio
                if (config_lookup_float(&cfg, "sst.particle.st_ratio", &valueDouble)) { 
                    params->sst->st_ratio = (float) valueDouble; 
                } 
                else { 
                    printf("Missing: sst.particle.st_ratio\n"); 
                    exit(EXIT_FAILURE); 
                }    
        
                // ve_alpha
                if (config_lookup_float(&cfg, "sst.particle.ve_alpha", &valueDouble)) { 
                    params->sst->ve_alpha = (float) valueDouble; 
                } 
                else { 
                    printf("Missing: sst.particle.ve_alpha\n"); 
                    exit(EXIT_FAILURE); 
                }    
        
                // ve_beta
                if (config_lookup_float(&cfg, "sst.particle.ve_beta", &valueDouble)) { 
                    params->sst->ve_beta = (float) valueDouble; 
                } 
                else { 
                    printf("Missing: sst.particle.ve_beta\n"); 
                    exit(EXIT_FAILURE); 
                }    

                // ve_ratio
                if (config_lookup_float(&cfg, "sst.particle.ve_ratio", &valueDouble)) { 
                    params->sst->ve_ratio = (float) valueDouble; 
                } 
                else { 
                    printf("Missing: sst.particle.ve_ratio\n"); 
                    exit(EXIT_FAILURE); 
                }    

                // ac_alpha
                if (config_lookup_float(&cfg, "sst.particle.ac_alpha", &valueDouble)) { 
                    params->sst->ac_alpha = (float) valueDouble; 
                } 
                else { 
                    printf("Missing: sst.particle.ac_alpha\n"); 
                    exit(EXIT_FAILURE); 
                }    

                // ac_beta
                if (config_lookup_float(&cfg, "sst.particle.ac_beta", &valueDouble)) { 
                    params->sst->ac_beta = (float) valueDouble;
                } 
                else { 
                    printf("Missing: sst.particle.ac_beta\n"); 
                    exit(EXIT_FAILURE); 
                }    

                // ac_ratio
                if (config_lookup_float(&cfg, "sst.particle.ac_ratio", &valueDouble)) { 
                    params->sst->ac_ratio = (float) valueDouble; 
                } 
                else { 
                    printf("Missing: sst.particle.ac_ratio\n"); 
                    exit(EXIT_FAILURE); 
                }    
        
                // Nmin
                if (config_lookup_float(&cfg, "sst.particle.Nmin", &valueDouble)) { 
                    params->sst->Nmin = (float) valueDouble; 
                } 
                else { 
                    printf("Missing: sst.particle.Nmin\n"); 
                    exit(EXIT_FAILURE); 
                }    

        config_destroy(&cfg);    

    }