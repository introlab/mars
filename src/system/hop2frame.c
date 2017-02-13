    
    #include "hop2frame.h"

    hop2frame_obj * hop2frame_construct_zero(const unsigned int hopSize, const unsigned int frameSize) {

        hop2frame_obj * obj;

        obj = (hop2frame_obj *) malloc(sizeof(hop2frame_obj));

        obj->hopSize = hopSize;
        obj->frameSize = frameSize;

        return obj;

    }

    void hop2frame_destroy(hop2frame_obj * obj) {

        free((void *) obj);

    }

    void hop2frame_process(hop2frame_obj * obj, const hops_obj * hops, frames_obj * frames) {

        unsigned int iSignal;
        unsigned int iSample;

        for (iSignal = 0; iSignal < hops->nSignals; iSignal++) {

            memmove(&(frames->array[iSignal][0]),
                    &(frames->array[iSignal][obj->hopSize]),
                    sizeof(float) * (obj->frameSize-obj->hopSize));

            memcpy(&(frames->array[iSignal][(obj->frameSize-obj->hopSize)]),
                   &(hops->array[iSignal][0]),
                   sizeof(float) * obj->hopSize);

        }        

    }