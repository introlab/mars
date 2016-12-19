
    #include "phasex2phasex.h"

    phasex2phasex_obj * phasex2phasex_construct(const unsigned int frameSize, const unsigned int bufferSize) {

        phasex2phasex_obj * obj;
        unsigned int iFrame;
        vector_float * phasex;

        obj = (phasex2phasex_obj *) malloc(sizeof(phasex2phasex_obj));

        obj->frameSize = frameSize;
        obj->halfFrameSize = frameSize/2+1;
        obj->bufferSize = bufferSize;

        obj->fifo = fifo_construct(obj->bufferSize);

        for (iFrame = 0; iFrame < obj->bufferSize; iFrame++) {

            phasex = vector_float_malloc(obj->halfFrameSize*2);
            vector_float_zero(phasex);

            fifo_push(obj->fifo, (void *) phasex);

        }

        obj->runningSum = vector_float_malloc(obj->halfFrameSize*2);
        vector_float_zero(obj->runningSum);

        return obj;

    }

    void phasex2phasex_destroy(phasex2phasex_obj * obj) {

        unsigned int iFrame;
        vector_float * phasex;

        for (iFrame = 0; iFrame < obj->bufferSize; iFrame++) {

            phasex = (vector_float *) fifo_pop(obj->fifo);
            vector_float_free(phasex);                        

        }

        fifo_destroy(obj->fifo);

        vector_float_free(obj->runningSum);

        free((void *) obj);

    }

    int phasex2phasex_process(phasex2phasex_obj * obj, const vector_float * phase12, vector_float * phase12smooth) {

        vector_float * phasex;
        unsigned int iElement;

        phasex = fifo_pop(obj->fifo);

        for (iElement = 0; iElement < (obj->halfFrameSize*2); iElement++) {

            obj->runningSum->array[iElement] -= phasex->array[iElement];
            obj->runningSum->array[iElement] += phase12->array[iElement];

        }

        vector_float_copy(phase12,phasex);

        fifo_push(obj->fifo,phasex);

        vector_float_copy(obj->runningSum,phase12smooth);

    }