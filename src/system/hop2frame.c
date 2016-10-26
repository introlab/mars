    
    #include "hop2frame.h"

    hop2frame_obj * hop2frame_construct(const unsigned short hopSize, const unsigned short frameSize) {

        hop2frame_obj * obj;
        unsigned short iSample;

        obj = (hop2frame_obj *) malloc(sizeof(hop2frame_obj));

        obj->hopSize = hopSize;
        obj->frameSize = frameSize;

        obj->frame = vector_float_malloc(frameSize);
        
        for (iSample = 0; iSample < frameSize; iSample++) {
            
            obj->frame->array[iSample] = 0.0f;

        }

        return obj;

    }

    void hop2frame_destroy(hop2frame_obj * obj) {

        vector_float_free(obj->frame);
        free((void *) obj);

    }

    int hop2frame_process(hop2frame_obj * obj, const vector_float * hop, vector_float * frame) {

        unsigned short iSample;

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