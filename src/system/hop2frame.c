    
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

    void hop2frame_process_single(hop2frame_obj * obj, const hop_obj * hop, frame_obj * frame) {

        unsigned int iSample;

        for (iSample = 0; iSample < (obj->frameSize-obj->hopSize); iSample++) {
            frame->array[iSample] = frame->array[iSample+obj->hopSize];
        }
        for (iSample = 0; iSample < obj->hopSize; iSample++) {
        	frame->array[iSample+(obj->frameSize-obj->hopSize)] = hop->array[iSample];
        }

    }

    void hop2frame_process_many(hop2frame_obj * obj, const hops_obj * hops, frames_obj * frames) {

        unsigned int iSignal;

        for (iSignal = 0; iSignal < hops->nSignals; iSignal++) {
            hop2frame_process_single(obj,hops->array[iSignal],frames->array[iSignal]);
        }        

    }