    
    #include "analysis.h"

    analysis_obj * analysis_construct(const unsigned int hopSize, const unsigned int frameSize) {

        analysis_obj * obj;
        unsigned int iSample;

        obj = (analysis_obj *) malloc(sizeof(analysis_obj));

        obj->hopSize = hopSize;
        obj->frameSize = frameSize;

        obj->frame = vector_float_malloc(frameSize);
        
        for (iSample = 0; iSample < frameSize; iSample++) {
            
            obj->frame->array[iSample] = 0.0f;

        }

        return obj;

    }

    void analysis_destroy(analysis_obj * obj) {

        vector_float_free(obj->frame);
        free((void *) obj);

    }

    int analysis_process(analysis_obj * obj, const vector_float * hop, vector_float * frame) {

        unsigned int iSample;

        for (iSample = 0; iSample < (obj->frameSize-obj->hopSize); iSample++) {

            obj->frame->array[iSample] = obj->frame->array[obj->hopSize+iSample];
            frame->array[iSample] = obj->frame->array[iSample];

        }

        for (iSample = 0; iSample < obj->hopSize; iSample++) {

            obj->frame->array[obj->frameSize-obj->hopSize+iSample] = hop->array[iSample];
            frame->array[obj->frameSize-obj->hopSize+iSample] = obj->frame->array[obj->frameSize-obj->hopSize+iSample];

        }

        return 0;

    }