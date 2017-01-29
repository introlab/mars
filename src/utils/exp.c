
    #include "exp.h"

    exp_obj * exp_construct(const float minX, const float maxX, const unsigned int N) {

        exp_obj * obj;
        unsigned int n;
        float x;

        obj = (exp_obj *) malloc(sizeof(exp_obj));

        obj->minX = minX;
        obj->maxX = maxX;
        obj->N = N;
        obj->delta = (maxX-minX) / ((float) (N-1));

        obj->values = (float *) malloc(sizeof(float) * N);

        for (n = 0; n < N; n++) {
            
            x = (obj->delta * (float) n) + obj->minX;
            obj->values[n] = expf(x);

        }

        return obj;

    }

    void exp_destroy(exp_obj * obj) {

        free((void *) obj->values);
        free((void *) obj);

    }

    float exp_estimate(const exp_obj * obj, const float x) {

        unsigned int n;

        if (x < obj->minX) {
            n = 0;
        }
        else if (x > obj->maxX) {
            n = obj->N - 1;
        }
        else {
            n = (unsigned int) roundf(((x - obj->minX) / obj->delta));    
        }

        return (obj->values[n]);

    }
