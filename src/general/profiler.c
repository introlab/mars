
    #include "profiler.h"

    profiler_obj * profiler_construct_zero(const unsigned int fS) {

        profiler_obj * obj;

        obj = (profiler_obj *) malloc(sizeof(profiler_obj));

        obj->resampling = 0.0f;
        obj->stft = 0.0f;
        obj->ssl = 0.0f;
        obj->sst = 0.0f;
        obj->duration = 0.0f;
        
        obj->fS = (float) fS;

        return obj;

    }

    void profiler_destroy(profiler_obj * obj) {

        free((void *) obj);

    }
