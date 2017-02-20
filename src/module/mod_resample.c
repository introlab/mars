    
    #include "mod_resample.h"

    mod_resample_obj * mod_resample_construct(const mod_resample_cfg * cfg) {

        mod_resample_obj * obj;
        unsigned int iHop;

        obj = (mod_resample_obj *) malloc(sizeof(mod_resample_obj));

        obj->nHops = cfg->nHops;
        obj->hopSizeIn = cfg->hopSizeIn;
        obj->hopSizeOut = cfg->hopSizeOut;

        if (cfg->hopSizeIn > cfg->hopSizeOut) {

            if ((cfg->hopSizeIn % cfg->hopSizeOut) != 0) {

                printf("Invalid hop size ratios.\n");
                exit(EXIT_FAILURE);

            }

            obj->hops = hops_construct_zero(cfg->nHops, cfg->hopSizeIn);
            obj->factor = cfg->hopSizeIn / cfg->hopSizeOut;
            obj->impulse = lowpass_init_factor(obj->factor);
            obj->firs = firs_construct_zero(obj->nHops, obj->impulse->nCoefficients);
            obj->hop2hop = hop2hop_construct_zero(obj->nHops);

        }
        else if (cfg->hopSizeIn < cfg->hopSizeOut) {

            if ((cfg->hopSizeOut % cfg->hopSizeIn) != 0) {

                printf("Invalid hop size ratios.\n");
                exit(EXIT_FAILURE);

            }

            obj->hops = hops_construct_zero(cfg->nHops, cfg->hopSizeOut);
            obj->factor = cfg->hopSizeOut / cfg->hopSizeIn;
            obj->impulse = lowpass_init_factor(obj->factor);
            obj->firs = firs_construct_zero(obj->nHops, obj->impulse->nCoefficients);
            obj->hop2hop = hop2hop_construct_zero(obj->nHops);

        }
        else {

            obj->hops = NULL;
            obj->factor = 1;
            obj->impulse = NULL;
            obj->firs = NULL;
            obj->hop2hop = NULL;

        }

        return obj;

    }

    void mod_resample_destroy(mod_resample_obj * obj) {

        if (obj->hops != NULL) {
            hops_destroy(obj->hops);
        }

        if (obj->firs != NULL) {
            firs_destroy(obj->firs);
        }
        
        if (obj->impulse != NULL) {
            impulse_destroy(obj->impulse);    
        }

        free((void *) obj);

    }

    void mod_resample_process(mod_resample_obj * obj, const msg_hops_obj * msg_hopsIn, msg_hops_obj * msg_hopsOut) {

        unsigned int iHop;

        if (obj->hopSizeIn > obj->hopSizeOut) {

            hop2hop_filter(obj->hop2hop,
                           msg_hopsIn->hops, 
                           obj->impulse, 
                           obj->firs,
                           obj->hops);

            hop2hop_downsample(obj->hop2hop,
                               obj->hops,
                               msg_hopsOut->hops);

        }
        else if (obj->hopSizeIn < obj->hopSizeOut) {

            hop2hop_upsample(obj->hop2hop,
                             msg_hopsIn->hops,
                             obj->hops);

            hop2hop_filter(obj->hop2hop,
                           obj->hops,
                           obj->impulse,
                           obj->firs,
                           msg_hopsOut->hops);

        }
        else {

            for (iHop = 0; iHop < obj->nHops; iHop++) {

                memcpy(msg_hopsOut->hops->array[iHop], 
                       msg_hopsIn->hops->array[iHop],
                       sizeof(float) * obj->hopSizeIn);

            }

        }

        msg_hopsOut->timeStamp = msg_hopsIn->timeStamp;

    }

    mod_resample_cfg * mod_resample_cfg_construct(void) {

        mod_resample_cfg * cfg;

        cfg = (mod_resample_cfg *) malloc(sizeof(mod_resample_cfg));

        cfg->nHops = 0;
        cfg->hopSizeIn = 0;
        cfg->hopSizeOut = 0;

        return cfg;

    }

    void mod_resample_cfg_destroy(mod_resample_cfg * cfg) {

        free((void *) cfg);

    }
