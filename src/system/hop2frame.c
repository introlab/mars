    
    #include "hop2frame.h"

    hop2frame_obj * hop2frame_construct(const unsigned int hopSize, const unsigned int frameSize, const unsigned int nMics) {

        hop2frame_obj * obj;
        unsigned int iMic;
        unsigned int iSample;

        obj = (hop2frame_obj *) malloc(sizeof(hop2frame_obj));

        obj->hopSize = hopSize;
        obj->frameSize = frameSize;
        obj->nMics = nMics;

        obj->frames = matrix_float_malloc(nMics,frameSize);
        
        for (iMic = 0; iMic < nMics; iMic++) {            

            for (iSample = 0; iSample < frameSize; iSample++) {
                
                obj->frames->array[iMic][iSample] = 0.0f;

            }

        }

        return obj;

    }

    void hop2frame_destroy(hop2frame_obj * obj) {

        matrix_float_free(obj->frames);
        free((void *) obj);

    }

    int hop2frame_process(hop2frame_obj * obj, const matrix_float * hops, matrix_float * frames) {

        unsigned int iMic;
        unsigned int iSample;

        for (iMic = 0; iMic < obj->nMics; iMic++) {                

            for (iSample = 0; iSample < (obj->frameSize-obj->hopSize); iSample++) {

                obj->frames->array[iMic][iSample] = obj->frames->array[iMic][obj->hopSize+iSample];
                frames->array[iMic][iSample] = obj->frames->array[iMic][iSample];

            }

            for (iSample = 0; iSample < obj->hopSize; iSample++) {

                obj->frames->array[iMic][obj->frameSize-obj->hopSize+iSample] = hops->array[iMic][iSample];
                frames->array[iMic][obj->frameSize-obj->hopSize+iSample] = obj->frames->array[iMic][obj->frameSize-obj->hopSize+iSample];

            }

        }

        return 0;

    }